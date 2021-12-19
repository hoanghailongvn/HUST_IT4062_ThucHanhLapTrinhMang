#include "../include/User.h"

using namespace std;

User::User(string username, string password) {
    this->state = OFFLINE;
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

void User::setClientAddr(struct sockaddr_in *input) {
    this->clientAddr = input;
}

bool User::isOnline() {
    return this->state == ONLINE || this->state == INGAME;
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