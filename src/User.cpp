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

User::State User::getState() {
    return this->state;
}

string User::getUsername() {
    return this->username;
}