#include "../include/User.h"

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

bool User::isOffline() {
    return this->state == OFFLINE;
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