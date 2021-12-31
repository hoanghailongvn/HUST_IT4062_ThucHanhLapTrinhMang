#ifndef ROOM_H
#define ROOM_H

#include "User.h"
#include <vector>
#include <string>

class UserClient;

class Room {
    protected:
    std::string name;
    std::vector<UserClient *> listUser;
    std::vector<bool> ready;
    void setup(std::string name, std::vector<UserClient *> listUser, std::vector<bool> ready);

    public:
    Room();
    Room(std::string name, std::vector<UserClient *> listUser, std::vector<bool> ready);
    ~Room();

    int getNumberUser();
    UserClient* getHost();
    std::string getName();
    void setReady(int stand, bool ready);
    void removeUser(UserClient *);
};

#endif