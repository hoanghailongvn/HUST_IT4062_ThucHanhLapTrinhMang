#include "../include/Room.h"
#include "../include/UserClient.h"
#include "../include/Game.h"
#include "../include/Server.h"

#include <algorithm>

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

void Room::resetReady() {
    int nb_user = this->getListUser().size();
    for(int i = 0; i < nb_user; i++) {
        this->ready.at(i) = false;
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

Game* Room::getGame() {
    return this->game;
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

void Room::startGame() {
    this->game = new Game(this->listUser);
    this->ingame = true;
    for(auto client: this->listUser) {
        client->getUser()->setInGame(true);
    }
}

void Room::endGame() {
    this->ingame = false;

    for(auto client: this->listUser) {
        client->getUser()->setInGame(false);
    }

    this->resetReady();

    Room *room = this;
    struct end_game res = Server::to_struct_end_game(room);
    char send_msg[BUFF_SIZE + 1];
    struct_to_message(&res, END_GAME, send_msg);

    for(auto dClient: this->disconnectedClient) {
        //Delete dclient from room's list client
        this->listUser.erase(remove(this->listUser.begin(), this->listUser.end(), dClient), this->listUser.end());
        //Delete dclient from server's list client
        Server::listClient.erase(remove(Server::listClient.begin(), Server::listClient.end(), dClient), Server::listClient.end());
        //deallocate
        delete dClient;
    }

    // Send end game message to online client
    for (auto client:room->getListUser()) {
        Server::sendToClient(client->getWritefd(), send_msg);
    }
    
    Server::updateRoom(room);
    delete this->game;
}

void Room::userDisconnectWhileInGame(UserClient *userClient) {
    this->disconnectedClient.push_back(userClient);
}

vector<UserClient *> Room::getOnlineClient() {
    vector<UserClient *> res;
    for(auto client: this->listUser) {
        if (find(this->disconnectedClient.begin(), this->disconnectedClient.end(), client) == this->disconnectedClient.end()) {
            res.push_back(client);
        }
    }
    return res;
}