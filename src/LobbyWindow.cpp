#include "../include/LobbyWindow.h"
#include "../include/RoomBox.h"

using namespace std;

LobbyWindow::LobbyWindow(sf::Font *font) {
    this->main = new sf::Text();
    this->main->setString("Lobby");
    this->main->setFont(*font);
    this->main->setFillColor(sf::Color::White);
    this->main->setCharacterSize(80);
    auto textRect = this->main->getGlobalBounds();
    this->main->setOrigin(textRect.left + textRect.width/2.f, textRect.top + textRect.height/2.f);
    this->main->setPosition(screenWidth/2.f, 50);

    this->userName = new sf::Text();
    this->userName->setFont(*font);
    this->userName->setFillColor(sf::Color::White);
    this->userName->setCharacterSize(20);
    this->userName->setPosition(10, 10);

    this->logout_btn = new Button(50, 550, 60, 20, font, "Logout", 16, sf::Color::Black, sf::Color::Magenta);
    this->joinRoom_btn = new Button(600, 450, 150, 100, font, "Join", 26, sf::Color::Black, sf::Color::Magenta);
    this->createRoom_btn = new Button(800, 450, 150, 100, font, "Create", 26, sf::Color::Black, sf::Color::Magenta);

    float x_box[4] = {100, 300, 500, 700};
    float y_box = 200;
    float x_size = 170;
    float y_size = 200;

    for(int i = 0; i < 4; i++) {
        auto newRoomBox = new RoomBox(x_box[i], y_box, x_size, y_size, font, false);
        this->listRoom.push_back(newRoomBox);
    }
}

LobbyWindow::~LobbyWindow() {
    delete this->main;
    delete this->userName;
    delete this->logout_btn;
}

void LobbyWindow::setUsername(string username) {
    this->userName->setString("User: " + username);
}

void LobbyWindow::update(sf::Vector2f mousePos) {
    this->logout_btn->update(mousePos);
    this->createRoom_btn->update(mousePos);
    this->joinRoom_btn->update(mousePos);
}

void LobbyWindow::drawTo(sf::RenderTarget &target) {
    target.draw(*this->main);
    target.draw(*this->userName);
    this->logout_btn->drawTo(target);
    this->createRoom_btn->drawTo(target);
    this->joinRoom_btn->drawTo(target);

    for(int i = 0; i < 4; i++) {
        this->listRoom.at(i)->drawTo(target);
    }
}

bool LobbyWindow::logoutPressed(char *message) {
    if (this->logout_btn->isPressed()) {
        rq_logout rq;
        struct_to_message(&rq, RQ_LOGOUT, message);
        return true;
    }
    return false;
}

bool LobbyWindow::joinPressed(char *message) {
    if (this->joinRoom_btn->isPressed()) {
        rq_join_room rq;
        struct_to_message(&rq, RQ_JOIN_ROOM, message);
        return true;
    }
    return false;
}

bool LobbyWindow::createRoomPressed() {
    if (this->createRoom_btn->isPressed()) {
        return true;
    }
    return false;
}

void LobbyWindow::updateRoom(struct update_lobby input) {
    int nb_room = input.name.size();
    for(int i = 0; i < 4; i++) {
        if (i < nb_room) {
            this->listRoom.at(i)->setup(input.name.at(i), input.number_user.at(i), input.ingame.at(i), true);
        } else {
            this->listRoom.at(i)->setExist(false);
        }
    }
}
