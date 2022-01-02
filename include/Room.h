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
    bool ingame = false;
    void setup(std::string name, std::vector<UserClient *> listUser, std::vector<bool> ready);

    public:
    Room();
    Room(std::string name, std::vector<UserClient *> listUser, std::vector<bool> ready);
    ~Room();

    int getNumberUser();
    UserClient* getHost();
    std::string getName();
    std::vector<UserClient *> getListUser();
    std::vector<bool> getReady();
    void setReady(int stand, bool ready);
    void addUser(UserClient *);
    void removeUser(UserClient *);
    bool isIngame();
};

#endif