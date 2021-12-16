#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include "tcp_server.h"
#define BACKLOG 5 
#define BUFF_SIZE 1024
#define MAX_SIZE 256
#define FILENAME "account.txt"


Node *createNode(Account account) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->account = account;
    newNode->next = NULL;
    return newNode;
}

Node *addHead(Node *head, Account account) {
    Node *newNode = createNode(account);
    if (head == NULL) return newNode;
    newNode->next = head;
    return newNode;
}

Node *searchNode(Node *head, char *name) {
    Node *temp = head;
    while (temp != NULL && strcmp(temp->account.name, name) != 0) {
        temp = temp->next;
    }
    return temp;
}

void freeList(Node *head) {
    Node *temp = head;
    while (temp != NULL) {
        head = head->next;
        free(temp);
        temp = head;
    }
}

Node *readFile(char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("  [!] Cannot open file \"%s\"\n", filename);
        exit(1);
    }
    Node *head = NULL;
    Account account;
    while (!feof(fp)) {
        fscanf(fp, "%s %s %d\n", account.name, account.passwd, &account.status);
        account.number_of_login = 0;
        head = addHead(head, account);
    }
    fclose(fp);
    return head;
}

Account getAccount(char *string) {
    int len = strlen(string);
    Account account;
    strcpy(account.name, string);
    int i = 0;
    while (i < len) {
        if (account.name[i] == '\n') {
            account.name[i] = '\0';
            break;
        }
        i++;
    }
    strcpy(account.passwd, &string[i+1]);
    return account;
}

int checkAccount(Node *head, char *name, char *passwd) {
    Node *find = searchNode(head, name);
    if (!find) return -2; 
    if (strcmp(find->account.passwd, passwd) != 0) return 0; 
    if (find->account.status == 0) return -1; 
    return 1; 
}

void changeStateUser(Node *head, char *filename) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        printf("  [!] Cannot open file \"%s\"\n", filename);
        exit(1);
    }
    Node *temp = head;
    while(temp) {
        if(temp->next == NULL)
            fprintf(fp, "%s %s %d", temp->account.name, temp->account.passwd, temp->account.status);
        else fprintf(fp, "%s %s %d\n", temp->account.name, temp->account.passwd, temp->account.status);

        temp = temp->next;
    }
    fclose(fp);
}



int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: ./server PortNumber\n");
        return -1;
    }
    int listen_sock, conn_sock; 
    char recv_data[BUFF_SIZE];
    int bytes_sent, bytes_received;
    struct sockaddr_in server; 
    struct sockaddr_in client; 
    socklen_t sin_size;

   
    if ((listen_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("\nError ");
        return 0;
    }

   
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[1])); 
    server.sin_addr.s_addr = htonl(INADDR_ANY); 
    if (bind(listen_sock, (struct sockaddr *)&server, sizeof(server)) == -1) {
        perror("\nError ");
        return 0;
    }

    if (listen(listen_sock, BACKLOG) == -1) {
        perror("\nError ");
        return 0;
    }

    while (1) {
        sin_size = sizeof(struct sockaddr_in);
        if ((conn_sock = accept(listen_sock, (struct sockaddr *)&client, &sin_size)) == -1)
            perror("\nError ");

        printf("You got a connection from %s\n", inet_ntoa(client.sin_addr));

        Node *head = readFile(FILENAME);
        Node *find = NULL;
        Account account;
        int isCorrect = 0;
        char reply[MAX_SIZE];
        char currUser[MAX_SIZE/2];
        while (1) {
            bytes_received = recv(conn_sock, recv_data, BUFF_SIZE - 1, 0);
            if (bytes_received <= 0) {
                printf("\nConnection closed");
                break;
            }
            recv_data[bytes_received] = '\0';
            if (strcmp(recv_data, "Bye") == 0) {
                sprintf(reply, "Goodbye %s", currUser);
            } else {
                account = getAccount(recv_data);
                isCorrect = checkAccount(head, account.name, account.passwd);
                switch (isCorrect) {
                    case -2:
                    case -1:
                        strcpy(reply, "0"); 
                        break;
                    case 0:
                        find = searchNode(head, account.name);
                        find->account.number_of_login++;
                        if(find->account.number_of_login <= 5) {
                            strcpy(reply, "1"); 
                        } else {
                            strcpy(reply, "2"); 
                            find->account.status = 0;
                            changeStateUser(head, FILENAME);
                        }
                        break;
                    case 1:
                        strcpy(reply, "3");
                        strcpy(currUser, account.name);
                        break;
                }
            }

            bytes_sent = send(conn_sock, reply, strlen(reply), 0);
            if (bytes_sent <= 0) {
                printf("\nConnection closed\n");
                break;
            }
        }
        freeList(head);
        close(conn_sock);
    }

    close(listen_sock);
    return 0;
}

