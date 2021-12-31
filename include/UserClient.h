#ifndef USERCLIENT_H
#define USERCLIENT_H

#include <string>
#include "User.h"

class Room;

class UserClient {
private:
    User *user;
    int clientfd, writefd;
    Room* room;

public:
    UserClient(User *user);
    ~UserClient();
 
    void setUser(User *user);
    void setClientfd(int clientfd);
    void setWritefd(int writefd);
    void setRoom(Room *room);
    User* getUser();
    int getClientfd();
    int getWritefd();
    Room* getRoom();
};

#endif