#ifndef ROOM_H
#define ROOM_H

#include "User.h"
#include <vector>
#include <string>

class UserClient;
class Game;

class Room {
private:
    std::string name;
    std::vector<UserClient *> listUser;
    std::vector<bool> ready;
    bool ingame = false;
    void setup(std::string name, std::vector<UserClient *> listUser, std::vector<bool> ready);

    Game *game;
public:
    Room();
    Room(std::string name, std::vector<UserClient *> listUser, std::vector<bool> ready);
    ~Room();

    int getNumberUser();
    UserClient* getHost();
    std::string getName();
    std::vector<UserClient *> getListUser();
    std::vector<bool> getReady();
    Game* getGame();
    void setReady(UserClient *);
    void setReady(UserClient *, bool ready);
    void resetReady();
    void setInGame(bool);
    void addUser(UserClient *);
    void removeUser(UserClient *);
    bool isIngame();
    void startGame();

};

#endif