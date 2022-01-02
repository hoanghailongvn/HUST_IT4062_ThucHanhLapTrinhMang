#include "../include/RoomBox.h"

using namespace std;

RoomBox::RoomBox(float x, float y, float width, float height, sf::Font *font, bool exist) {
    this->font = font;

    this->shape.setPosition(sf::Vector2f(x, y));
    this->shape.setSize(sf::Vector2f(width, height));
    this->shape.setOutlineColor(sf::Color::White);
    this->shape.setOutlineThickness(8);
    this->shape.setFillColor(sf::Color::Black);

    this->roomname.setPosition(sf::Vector2f(x + 10, y + 10));
    this->roomname.setFont(*this->font);
    this->roomname.setCharacterSize(30);

    this->nb_user.setPosition(sf::Vector2f(x + 10, y + 90));
    this->nb_user.setFont(*this->font);
    this->nb_user.setCharacterSize(30);

    this->state.setPosition(sf::Vector2f(x + 10, y + 130));
    this->state.setFont(*this->font);
    this->nb_user.setCharacterSize(30);

    this->exist = exist;
}

RoomBox::~RoomBox() {}

void RoomBox::setup(string roomname, int nb_user, bool ingame, bool exist) {
    this->exist = exist;
    this->roomname.setString("Room:\n" + roomname);
    this->nb_user.setString(to_string(nb_user) + "/4");
    if (ingame) {
        this->state.setString("Ingame");
    } else {
        this->state.setString("");
    }
}

void RoomBox::update(sf::Vector2f mousePos){

}

void RoomBox::drawTo(sf::RenderTarget& target) {
    if(this->exist) {
        target.draw(this->shape);
        target.draw(this->roomname);
        target.draw(this->nb_user);
        target.draw(this->state);
    }
}

void RoomBox::setExist(bool exist) {
    this->exist = exist;
}