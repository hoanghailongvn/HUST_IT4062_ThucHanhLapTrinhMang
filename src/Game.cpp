#include "../include/Game.h"
#include "../include/Server.h"

using namespace std;

Game::Game(vector<UserClient *> listUser) {
    this->listUser = listUser;
    this->updateRandomTarget();


    //Game Logic
    this->time_left = GAME_LENGTH;
    this->endGame = false;

    int base_x = 1;
    int base_y = 2;

    for (int i = 0; i < this->listUser.size(); i++){
        this->x.push_back(base_x + i);
        this->y.push_back(base_y);
        this->nb_word_done.push_back(0);
        this->point.push_back(0);
    }
}

Game::~Game() {}

vector<int> Game::getX() {
    return this->x;
}
vector<int> Game::getY() {
    return this->y;
}
vector<int> Game::getPoint() {
    return this->point;
}
vector<int> Game::getNbWordDone() {
    return this->nb_word_done;
}
int Game::getTimeLeft() {
    return this->time_left;
}


void Game::updateRandomTarget() {
    this->target = Server::listTarget.at(rand() % NB_TARGET);
}

void Game::secondPass() {
    //////
    this->time_left--;
    if (time_left <= 0) {
        this->endGame = true;
    }
}