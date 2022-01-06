#include "../include/UserClient.h"
#include "../include/Room.h"

using namespace std;

UserClient::UserClient(User *user) {
    this->user = user;
}

UserClient::~UserClient() {}

void UserClient::setUser(User *user) {
    this->user = user;
}

void UserClient::setClientfd(int clientfd) {
    this->clientfd = clientfd;
}

void UserClient::setWritefd(int writefd) {
    this->writefd = writefd;
}

void UserClient::setRoom(Room *room) {
    this->room = room;
    this->user->setRoom(room);
}

User* UserClient::getUser() {
    return this->user;
}

int UserClient::getClientfd(){
    return this->clientfd;
}

int UserClient::getWritefd() {
    return this->writefd;
}

Room* UserClient::getRoom() {
    return this->room;
}