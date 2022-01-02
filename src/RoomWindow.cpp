#include "../include/RoomWindow.h"

using namespace std;

RoomWindow::RoomWindow(sf::Font *font){
    this->font = font;

    float x_box[4] = {100, 300, 500, 700};
    float y_box = 200;
    float x_size = 170;
    float y_size = 200;
    sf::Color listColor[4] = {sf::Color::Red, sf::Color::Blue, sf::Color::Green, sf::Color::Yellow};

    for (int i = 0; i < 4; i++) {
        auto newUserBox = new UserBox(x_box[i], y_box, x_size, y_size, this->font, listColor[i]);
        this->userBoxList.push_back(newUserBox);
        this->userNameList.push_back("");
        this->ready.push_back(false);
    }

    this->main = new sf::Text();
    this->main->setString("Room: " + this->name);
    this->main->setFont(*font);
    this->main->setFillColor(sf::Color::White);
    this->main->setCharacterSize(60);
    this->main->setPosition(0, 0);

    this->start_btn = new Button(700, 450, 150, 100, font, "Start", 36, sf::Color::Black, sf::Color::Magenta);
    this->ready_btn = new Button(700, 450, 150, 100, font, "Ready", 36, sf::Color::Black, sf::Color::Magenta);
    this->back_btn = new Button(50, 550, 60, 20, font, "Back", 16, sf::Color::Black, sf::Color::Magenta);
}

RoomWindow::~RoomWindow() {
    for (int i = 0; i < 4; i++) {
        delete this->userBoxList.at(i);
    }
}

string RoomWindow::getName() {
    return this->name;
}

void RoomWindow::setName(string name) {
    this->name = name;
}

void RoomWindow::update(sf::Vector2f mousePos) {
    this->back_btn->update(mousePos);
    this->ready_btn->update(mousePos);
    this->start_btn->update(mousePos);   
}

void RoomWindow::updateRoom(struct update_room input) {
    this->name = input.room_name;
    this->main->setString("Room: " + this->name);

    int nb_user = input.username.size();
    for(int i = 0; i < 4; i++) {
        if (i < nb_user) {
            this->userBoxList.at(i)->setup(input.username.at(i), input.ready.at(i));
            this->userNameList.at(i) = input.username.at(i);
            this->ready.at(i) = input.ready.at(i);
        } else {
            this->userBoxList.at(i)->setup("", false);
            this->userNameList.at(i) = "";
            this->ready.at(i) = false;
        }
    }
}

void RoomWindow::drawTo(sf::RenderTarget &target, UserClient *userClient) {
    target.draw(*this->main);
    this->back_btn->drawTo(target);
    if (this->userNameList.at(0).compare(userClient->getUser()->getUsername()) == 0) {
        this->start_btn->drawTo(target);
    } else {
        this->ready_btn->drawTo(target);
    }

    for (int i = 0; i < 4; i++) {
        this->userBoxList.at(i)->drawTo(target);
    }
}

bool RoomWindow::backPressed(char *message) {
    if (this->back_btn->isPressed()) {
        rq_exit_room rq;
        struct_to_message(&rq, RQ_EXIT_ROOM, message);
        return true;
    }
    return false;
}