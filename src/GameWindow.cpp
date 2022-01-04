#include "../include/GameWindow.h"
#include "../include/Message.h"
using namespace std;

GameWindow::GameWindow(sf::Font *font) {
}

GameWindow::~GameWindow(){}

void GameWindow::setUsernameList(vector<string> usernameList) {
    this->userNameList = usernameList;
}

void GameWindow::updateGame(struct update_game input) {
    this->time_left = input.time_left;
    this->x = input.x;
    this->y = input.y;
    this->nb_word_done = input.nb_word_done;
    this->point = input.point;
}

void GameWindow::updateTarget(struct update_target input) {
    this->target = input.target;
}
