#ifndef ROOM_H
#define ROOM_H

#include "User.h"
#include <vector>
#include <string>

class Room {
    private:
    std::string name;
    User *host;
    std::vector<User *> listMember;

    public:
    Room(std::string name, User *host);
    ~Room();

    int getNumberMember();


};

#endif