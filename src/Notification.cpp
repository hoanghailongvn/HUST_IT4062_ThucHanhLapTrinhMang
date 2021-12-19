#include "../include/Notification.h"

Notification::Notification(sf::Font *font) {
    this->shape.setPosition(sf::Vector2f(200, 100));
    this->shape.setSize(sf::Vector2f(screenWidth - 400, screenHeight - 200));
    this->shape.setFillColor(sf::Color::Black);
    this->shape.setOutlineColor(sf::Color::White);
    this->shape.setOutlineThickness(2);

    this->main.setFont(*font);
    this->sub.setFont(*font);
    this->main.setFillColor(sf::Color::White);
    this->sub.setFillColor(sf::Color::White);

    this->main.setPosition(this->shape.getPosition().x + 10, this->shape.getPosition().y + 10);
    this->sub.setPosition(this->shape.getPosition().x + 10, this->shape.getPosition().y + 100);
}

Notification::~Notification() {

}

void Notification::setText(std::string main, int main_size, std::string sub, int sub_size) {
    this->main.setString(main);
    this->sub.setString(sub);

    this->main.setCharacterSize(main_size);
    this->sub.setCharacterSize(sub_size);
}

void Notification::drawTo(sf::RenderTarget& target) {
    target.draw(this->shape);
    target.draw(this->main);
    target.draw(this->sub);
}