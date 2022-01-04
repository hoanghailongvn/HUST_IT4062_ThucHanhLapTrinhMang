#ifndef CHARACTERBOX_H
#define CHARACTERBOX_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <string>

class CharacterBox {
private:
    sf::RectangleShape shape;
    sf::Text character;
    sf::Font *font;
public:
    CharacterBox(float x, float y, float size, sf::Font *font, char character);
    ~CharacterBox();

    void drawTo(sf::RenderTarget& target);
};


#endif