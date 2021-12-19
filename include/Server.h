#ifndef SERVER_H
#define SERVER_H

#include "User.h"
#include "GameConfig.h"
#include "Message.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string.h>
#include <fstream>

#include <arpa/inet.h> // in_addr
#include <sys/socket.h> // socklen_t
#include <netdb.h> //dns
#include <unistd.h> //close, fork
#include <sys/wait.h> //waitpid

void sig_chld(int signo);

class Server {
private:
    std::vector<User *> listUser;
    int listenfd;
    char buff[BUFF_SIZE + 1];
    struct sockaddr_in servAddr;
    pid_t pid;


public:
    Server();
    ~Server();

    void run();

    void rq_register();
    void rq_login();

    void sendToClient(int connfd);
    void loadUserData(std::string path);
};

#endif