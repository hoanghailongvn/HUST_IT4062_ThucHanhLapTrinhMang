/*
UserBox used in room
*/

#ifndef USERBOX_H
#define USERBOX_H

#include "Room.h"
#include "Button.h"

#include <iostream>
#include <string>
#include "GameConfig.h"
#include "Button.h"
#include "Textbox.h"
#include "Message.h"
#include "UserClient.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class UserBox {
private:
    sf::RectangleShape shape;
    sf::CircleShape circle_shape;
    sf::Text username, ready_text;
    sf::Font *font;

    bool ready;

public:
    UserBox(float x, float y, float width, float height, sf::Font *font, sf::Color userColor);
    ~UserBox();

    void setup(std::string name, bool ready);

    void update(sf::Vector2f mousePos);
    void drawTo(sf::RenderTarget& target);
};

#endif