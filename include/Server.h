#ifndef SERVER_H
#define SERVER_H

#include "User.h"
#include "UserClient.h"
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

class Server {
private:
    int listenfd;
    struct sockaddr_in servAddr;

    static std::vector<User *> listUser;
    static std::vector<Room *> listRoom;
    static std::vector<UserClient *> listClient;

    std::vector<pthread_t> threads;

public:
    Server();
    ~Server();

    void run();

    static void rq_register(char *rq_register, char *rp_register);
    static void rq_login(char *rq_login, char *rp_login, int connfd, UserClient *&userClient);
    static void rq_logout(char *rq_logout, char *rp_logout, UserClient *&userClient);
    static void rq_createRoom(char *rq_createRoom, char *rp_createRoom, UserClient *&userClient);
    static void rq_exitRoom(char *rq_exitRoom, UserClient *&userClient);
    static void rq_joinRoom(char *rq_joinRoom, char *rp_joinRoom, UserClient *&userClient);

    static struct update_lobby to_struct_update_lobby();
    static void updateLobby();
    static void updateLobby(UserClient *&userClient);

    static void rcvFromClient(int connfd, char *rcv_message);
    static void sendToClient(int connfd, char *send_message);
    void loadUserData(std::string path);

    static void* routine1(void *);
    static void* routine2(void *);
};


#endif