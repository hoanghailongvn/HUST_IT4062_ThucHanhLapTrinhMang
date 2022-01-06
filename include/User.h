#ifndef USER_H
#define USER_H

#include <string>
#include "GameConfig.h"

class Room;

enum State {OFFLINE, ONLINE};

class User {
private:
    State state;
    std::string username;
    std::string password;
    bool inGame;
    Room *room;
public:
    User(std::string username, std::string password);
    ~User();

    std::string getUsername();
    bool checkPassword(std::string input);
    bool isOnline();
    void setState(State state);
    State getState();
    void setInGame(bool);
    void setRoom(Room *room);
    bool isInGame();
    
};

#endif