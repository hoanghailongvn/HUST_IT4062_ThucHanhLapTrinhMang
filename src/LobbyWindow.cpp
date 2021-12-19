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

    this->logout_btn = new Button(50, 550, 60, 20, font, "Logout", 16, sf::Color::Black, sf::Color::Magenta);
}

LobbyWindow::~LobbyWindow() {
    delete this->main;
    delete this->logout_btn;
}

void LobbyWindow::update(sf::Vector2f mousePos) {
    this->logout_btn->update(mousePos);
}

void LobbyWindow::drawTo(sf::RenderTarget &target) {
    target.draw(*this->main);
    this->logout_btn->drawTo(target);
}

bool LobbyWindow::logoutPressed() {
    return this->logout_btn->isPressed();
}