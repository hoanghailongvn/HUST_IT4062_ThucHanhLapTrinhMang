#include "../include/Room.h"

using namespace std;

Room::Room(string name, User *host) {
    this->name = name;
    this->host = host;
    this->listMember.push_back(host);
}

Room::~Room() {}

int Room::getNumberMember() {
    return this->listMember.size();
}