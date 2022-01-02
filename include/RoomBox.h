/*
RoomBox used in lobby
*/

#ifndef ROOMBOX_H
#define ROOMBOX_H

#include "LobbyWindow.h"

#include <iostream>
#include <string>
#include "GameConfig.h"
#include "Button.h"
#include "Textbox.h"
#include "Message.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class RoomBox {
private:
    sf::RectangleShape shape;
    sf::Text roomname;
    sf::Text nb_user;
    sf::Text state;
    sf::Font *font;

    bool exist;
public:
    RoomBox(float x, float y, float width, float height, sf::Font *font, bool exist);
    ~RoomBox();

    void setup(std::string roomname, int nb_user, bool state, bool exist);
    void setExist(bool exist);

    void update(sf::Vector2f mousePos);
    void drawTo(sf::RenderTarget& target);
};

#endif