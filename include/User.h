#ifndef USER_H
#define USER_H

#include <string>
#include "GameConfig.h"

enum State {OFFLINE, ONLINE, INGAME};

class User {
private:
    State state;
    std::string username;
    std::string password;
public:
    User(std::string username, std::string password);
    ~User();


    std::string getUsername();
    void setState(State state);
    State getState();
};

#endif