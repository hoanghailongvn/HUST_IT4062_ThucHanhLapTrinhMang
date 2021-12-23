#include "../include/UserBox.h"

using namespace std;

UserBox::UserBox(float x, float y, float width, float height, 
    sf::Font *font, sf::Color userColor) 
{
    this->ready = ready;
    this->font = font;

    this->shape.setPosition(sf::Vector2f(x, y));
    this->shape.setSize(sf::Vector2f(width, height));
    this->shape.setOutlineColor(sf::Color::White);
    this->shape.setOutlineThickness(8);
    this->shape.setFillColor(sf::Color::Black);

    this->circle_shape.setPosition(sf::Vector2f(x + 55, y + 100));
    this->circle_shape.setRadius(30);
    this->circle_shape.setFillColor(userColor);
    this->circle_shape.setOutlineColor(sf::Color::White);
    this->circle_shape.setOutlineThickness(3);

    this->username.setPosition(sf::Vector2f(x + 10, y + 10));
    this->username.setFont(*this->font);
    this->username.setCharacterSize(30);
}

UserBox::~UserBox() {}

void UserBox::setup(string username, bool ready) {
    this->ready = ready;
    this->username.setString(username);
    this->username_string = username;
}

void UserBox::update(sf::Vector2f mousePos){

}

void UserBox::drawTo(sf::RenderTarget& target) {
    target.draw(this->shape);
    if(this->username_string.length() != 0) {
        target.draw(this->circle_shape);
        target.draw(this->username);
    }
}