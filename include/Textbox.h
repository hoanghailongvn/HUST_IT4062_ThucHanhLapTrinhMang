#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <string>

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class Textbox {
private:
    sf::Text textbox;
    std::ostringstream text;
    std::string textbase;
    bool isSelected;
    int limit;

    void inputLogic(int charTyped);
    void deleteLastChar();

public:
    Textbox(float x, float y, sf::Font *font, std::string textbase, int size, sf::Color color, bool sel, int limit);
    ~Textbox();

    void setSelected(bool sel);
    std::string getText();
    void drawTo(sf::RenderTarget &window);
    void typedOn(sf::Event ev);
    bool isPressed(sf::Vector2f mousePos);
    void refresh();

};

#endif