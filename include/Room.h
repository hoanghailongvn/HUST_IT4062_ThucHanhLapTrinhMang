#ifndef ROOM_H
#define ROOM_H

#include "User.h"
#include <vector>
#include <string>

class Room {
    protected:
    std::string name;
    std::vector<std::string> listUser;
    std::vector<bool> ready;
    void setup(std::string name, std::vector<std::string> listUser, std::vector<bool> ready);

    public:
    Room();
    Room(std::string name, std::vector<std::string> listUser, std::vector<bool> ready);
    ~Room();

    int getNumberUser();
    std::string getHost();
    std::string getName();
    void setReady(int stand, bool ready);
    void removeUser(std::string user);
};

#endif