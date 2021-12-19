#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <stdio.h>
#include <string.h>
#include "GameConfig.h"
#include "Window.h"

#include <arpa/inet.h> // in_addr
#include <sys/socket.h> // socklen_t
#include <netdb.h> //dns
#include <unistd.h> //close

class Client {
private:
    int clientfd;
    char buff[BUFF_SIZE + 1];
    struct sockaddr_in servAddr;
    
    Window window;
public:
    Client();
    ~Client();

    void communicate();
    void run();
    void closeSocket();
};

#endif