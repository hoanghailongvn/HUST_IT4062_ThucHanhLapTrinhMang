#include "../include/IntroWindow.h"

IntroWindow::IntroWindow(sf::Font *font) {
    this->main = new sf::Text();
    this->main->setString("W");
    this->main->setFont(*font);
    this->main->setFillColor(sf::Color::White);
    this->main->setCharacterSize(220);
    auto textRect = this->main->getGlobalBounds();
    this->main->setOrigin(textRect.left + textRect.width/2.f, textRect.top + textRect.height/2.f);
    this->main->setPosition(screenWidth/2.f, 150);

    this->register_btn = new Button(100, 300, 300, 100, font, "Register", 36, sf::Color::Black, sf::Color::Magenta, sf::Color::Black);
    this->login_btn = new Button(600, 300, 300, 100, font, "Login", 36, sf::Color::Black, sf::Color::Magenta, sf::Color::Black);
}

IntroWindow::~IntroWindow() {
    delete this->register_btn;
    delete this->login_btn;
    delete this->main;
}

void IntroWindow::update(sf::Vector2f mousePos) {
    this->register_btn->update(mousePos);
    this->login_btn->update(mousePos);
}

void IntroWindow::drawTo(sf::RenderTarget &target) {
    this->register_btn->drawTo(target);
    this->login_btn->drawTo(target);
    target.draw(*this->main);
}

bool IntroWindow::registerPressed() {
    return this->register_btn->isPressed();
}

bool IntroWindow::loginPressed() {
    return this->login_btn->isPressed();
}