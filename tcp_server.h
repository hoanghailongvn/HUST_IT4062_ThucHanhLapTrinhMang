#include <stdio.h> 
#define MAX_SIZE 256

typedef struct Account {
    char name[MAX_SIZE];
    char passwd[MAX_SIZE];
    int status;
    int number_of_login;
} Account;

typedef struct node {
    Account account;
    struct node *next;
} Node;


Node *createNode(Account account);
Node *addHead(Node *head, Account account);
Node *searchNode(Node *head, char *name);
void freeList(Node *head);

Node *readFile(char *filename);
Account getAccount(char *string);
int checkAccount(Node *head, char *name, char *passwd);
void changeStateUser(Node *head, char *filename);