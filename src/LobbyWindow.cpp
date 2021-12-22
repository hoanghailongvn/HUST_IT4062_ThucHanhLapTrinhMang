#include "../include/LobbyWindow.h"

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
}

bool LobbyWindow::logoutPressed(char *message) {
    if (this->logout_btn->isPressed()) {
        rq_logout rq;
        struct_to_message(&rq, RQ_LOGOUT, message);
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