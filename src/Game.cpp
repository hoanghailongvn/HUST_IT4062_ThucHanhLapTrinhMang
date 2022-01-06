#include "../include/Game.h"
#include "../include/Server.h"

#include <algorithm>

using namespace std;

Game::Game(vector<UserClient *> listUser) {
    this->listUser = listUser;

    //Game Logic
    this->time_left = GAME_LENGTH;

    vector<int> x_pos{2, 4, 2, 4};
    vector<int> y_pos{1, 1, 2, 2};

    for (int i = 0; i < this->listUser.size(); i++){
        this->x.push_back(x_pos.at(i));
        this->y.push_back(y_pos.at(i));
        this->nb_word_done.push_back(0);
        this->point.push_back(0);
    }

    this->updateRandomTarget();
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

string Game::getTarget() {
    return this->target;
}

void Game::updateRandomTarget() {
    this->target = Server::listTarget.at(rand() % NB_TARGET);
    fill(this->nb_word_done.begin(), this->nb_word_done.end(), 0);
}

void Game::secondPass() {
    this->time_left--;
}

bool Game::isEndGame() {
    if(this->time_left <= 0 || (*max_element(this->point.begin(), this->point.end()) >= MAX_POINT)) {
        return true;
    } 
    return false;
}

bool Game::receivAction(struct rq_action rq, UserClient *&userClient) {
    int position = -1;
    for(int i = 0; i < this->listUser.size(); i++) {
        cout << "ok" << i << endl;
        if (this->listUser.at(i) == userClient) {
            cout << "slkdjf" << endl;
            position = i;
        }
    }
    switch (rq.action)
    {
    case SPACE:
        char now_char;
        if(this->y.at(position) == 0) {
            now_char = 'a' + this->x.at(position) - 1;
        } else {
            now_char = 'a' + 5 + (this->y.at(position) - 1)* 7 + this->x.at(position);
        }

        cout << now_char << ":" << this->target.at(this->nb_word_done.at(position)) << endl;

        if(this->target.at(this->nb_word_done.at(position)) == now_char) {
            this->nb_word_done.at(position) += 1;
            if (this->nb_word_done.at(position) == this->target.length()) {
                this->point.at(position) += 1;
                this->updateRandomTarget();
                return true;
            }
        }
        break;
    case UP:
        this->y.at(position) = max(0, this->y.at(position) - 1);
        break;
    case DOWN:
        this->y.at(position) = min(3, this->y.at(position) + 1);
        break;
    case LEFT:
        if (this->y.at(position) == 0) {
            this->x.at(position) = max(1, this->x.at(position) - 1);
        } else {
            this->x.at(position) = max(0, this->x.at(position) - 1);
        }
        break;
    case RIGHT:
        if (this->y.at(position) == 0) {
            this->x.at(position) = min(5, this->x.at(position) + 1);
        } else {
            this->x.at(position) = min(6, this->x.at(position) + 1);
        }
        break;

    default:
        break;
    }
    return false;
}

void Game::setListUser(vector<UserClient *> input) {
    this->listUser = input;
}