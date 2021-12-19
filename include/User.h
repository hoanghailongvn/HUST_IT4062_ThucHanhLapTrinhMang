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

    struct sockaddr_in *clientAddr;
public:
    User(std::string username, std::string password);
    ~User();


    std::string getUsername();
    void setClientAddr(struct sockaddr_in *input);
    bool checkPassword(std::string input);
    bool isOnline();
    bool isOffline();
    void setState(State state);
    State getState();
};

#endif