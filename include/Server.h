#ifndef SERVER_H
#define SERVER_H

#include "User.h"
#include "Room.h"
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
#include <pthread.h>

void* routine(void *);

class Server {
private:
    int listenfd;
    struct sockaddr_in servAddr;

    static std::vector<User *> listUser;
    static std::vector<Room *> listRoom;

    std::vector<pthread_t> threads;

public:
    Server();
    ~Server();

    void run();

    static void rq_register(char *rq_register, char *rp_register);
    static void rq_login(char *rq_login, char *rp_login, int connfd, User *&clientUser);
    static void rq_logout(char *rq_logout, char *rp_logout, User *&clientUser);
    static void rq_createRoom(char *rq_createRoom, char *rp_createRoom, User *&clientUser);

    static void rcvFromClient(int connfd, char *rcv_message);
    static void sendToClient(int connfd, char *send_message);
    void loadUserData(std::string path);

    static void* routine(void *);
};

std::vector<User *> Server::listUser;
std::vector<Room *> Server::listRoom;


#endif