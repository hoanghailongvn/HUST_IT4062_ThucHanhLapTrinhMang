#include "../include/User.h"
#include "../include/Room.h"

using namespace std;

User::User(string username, string password) {
    this->state = OFFLINE;
    this->inGame = false;
    this->username = username;
    this->password = password;
}

User::~User() {}

void User::setState(State state) {
    this->state = state;
}

State User::getState() {
    return this->state;
}

bool User::isOnline() {
    return this->state == ONLINE;
}

string User::getUsername() {
    return this->username;
}

bool User::checkPassword(string input) {
    if (this->password.compare(input) == 0) {
        return true;
    } else {
        return false;
    }
}

void User::setInGame(bool input) {
    this->inGame = input;
}
bool User::isInGame() {
    return this->inGame;
}

void User::setRoom(Room *room) {
    this->room = room;
}