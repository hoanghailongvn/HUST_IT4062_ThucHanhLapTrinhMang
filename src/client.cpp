#include <iostream>
#include <stdio.h>
#include <string.h>

#include <arpa/inet.h> // in_addr
#include <sys/socket.h> // socklen_t
#include <netdb.h> //dns

#define BUFF_SIZE 1024

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cout << "Please input IP address of client and server port!!\n";
        return 1;
    }

    int port = atoi(argv[2]);

    int sockfd, rcvBytes, sendBytes;
    socklen_t len;
    char buff[BUFF_SIZE + 1];
    struct sockaddr_in server_addr, client_addr;

    // Construct socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Error: ");
        return 0;
    }
    
    // Define the address of the client
    bzero(&client_addr, sizeof(client_addr));
    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = inet_addr(argv[1]);
    if (bind(sockfd, (struct sockaddr *)&client_addr, sizeof(client_addr))) {
        perror("Error");
        return 1;
    }

    // Define the address of the server
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(port);

    cout << "Send to server: " << "\n";
    fgets(buff, BUFF_SIZE, stdin);

    len = sizeof(server_addr);
    sendBytes = sendto(sockfd, buff, strlen(buff), 0, (struct sockaddr *) &server_addr, len);

    if (sendBytes < 0) {
        perror("Error: ");
        return 0;
    }

    rcvBytes = recvfrom(sockfd, buff, BUFF_SIZE, 0, (struct sockaddr *) &server_addr, &len);

    if (rcvBytes < 0) {
        perror("Error: ");
        return 0;
    }
    buff[rcvBytes] = '\0';
    printf("Reply from server: %s", buff);

    return 0;
}

