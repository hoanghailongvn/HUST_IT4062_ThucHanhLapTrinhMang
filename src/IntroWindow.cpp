#include "../include/IntroWindow.h"

IntroWindow::IntroWindow(sf::Font *font) {
    this->register_btn = new Button(100, 300, 300, 100, font, "Register", 36, sf::Color::Black, sf::Color::Magenta, sf::Color::Black);
    this->login_btn = new Button(600, 300, 300, 100, font, "Login", 36, sf::Color::Black, sf::Color::Magenta, sf::Color::Black);
}

IntroWindow::~IntroWindow() {
    delete this->register_btn;
    delete this->login_btn;
}

void IntroWindow::update(sf::Vector2f mousePos) {
    this->register_btn->update(mousePos);
    this->login_btn->update(mousePos);
}

void IntroWindow::drawTo(sf::RenderTarget &target) {
    this->register_btn->drawTo(target);
    this->login_btn->drawTo(target);
}