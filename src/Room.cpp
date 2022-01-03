#include "../include/Room.h"
#include "../include/UserClient.h"

using namespace std;

Room::Room() {}

Room::Room(string name, vector<UserClient *> listUser, vector<bool> ready) {
    this->name = name;
    this->listUser = listUser;
    this->ready = ready;
}

Room::~Room() {}

void Room::setup(string name, vector<UserClient *> listUser, vector<bool> ready) {
    this->name = name;
    this->listUser = listUser;
    this->ready = ready;
}

void Room::setReady(UserClient *userClient) {
    int nb_user = this->getListUser().size();
    for(int i = 0; i < nb_user; i++) {
        if (userClient == this->getListUser().at(i)) {
            this->ready.at(i) = !this->ready.at(i);
            break;
        }
    }
}

void Room::setReady(UserClient *userClient, bool ready) {
    int nb_user = this->getListUser().size();
    for(int i = 0; i < nb_user; i++) {
        if (userClient == this->getListUser().at(i)) {
            this->ready.at(i) = ready;
            break;
        }
    }
}

string Room::getName() {
    return this->name;
}

int Room::getNumberUser() {
    return this->listUser.size();
}

vector<UserClient *> Room::getListUser() {
    return this->listUser;
}

vector<bool> Room::getReady() {
    return this->ready;
}


void Room::removeUser(UserClient *userClient) {
    for(int i = 0; i < this->listUser.size(); i++) {
        if(this->listUser.at(i) == userClient) {
            this->listUser.erase(this->listUser.begin() + i);
            break;
        }
    }
}

void Room::addUser(UserClient *userClient) {
    this->listUser.push_back(userClient);
    this->ready.push_back(false);
}

UserClient* Room::getHost() {
    if (this->listUser.size() > 0) {
        return this->listUser.at(0);
    } else {
        return nullptr;
    }
}

bool Room::isIngame() {
    return this->ingame;
}