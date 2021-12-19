#include "../include/Client.h"

Client::Client() {
    this->clientfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&this->servAddr, sizeof(this->servAddr));
    this->servAddr.sin_family = AF_INET;
    this->servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    this->servAddr.sin_port = htons(SERVER_PORT);
}

Client::~Client() {

}

void Client::communicate() {
    if (connect(this->clientfd, (sockaddr *)&this->servAddr, sizeof(this->servAddr))) {
        perror("Error: ");
        exit(1);
    }
}

void Client::run() {
        
    //Step 5: Communicate with server
    int ret;
    // Send message
    printf("Send to server: ");
    fgets(this->buff, BUFF_SIZE, stdin);
    ret = send(this->clientfd, this->buff, strlen(this->buff), 0);
    if (ret < 0) {
        perror("Error: ");
        exit(1);
    }

    //Receive echo message
    ret = recv(this->clientfd, buff, BUFF_SIZE, 0);
    if (ret < 0) {
        perror("Error");
        exit(1);
    }
    printf("Receive from server: %s\n", buff);
}

void Client::closeSocket() {
    close(this->clientfd);
}