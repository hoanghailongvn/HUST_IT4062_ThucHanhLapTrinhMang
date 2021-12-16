#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>
#include <ctime>
#include <sstream>
#include "GameConfig.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

enum button_states{BTN_IDLE, BTN_HOVER, BTN_ACTIVE};

class Button {
private:
    button_states buttonState;

    sf::RectangleShape shape;
    sf::Text text;
    
    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Color activeColor;

public:
    Button(float x, float y, float width, float height, 
        sf::Font *font, std::string text, int fontSize,
        sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
    ~Button();

    void update(sf::Vector2f mousePos);
    void drawTo(sf::RenderTarget& target);

    //Accessors
    const bool isPressed() const;
};

#endif