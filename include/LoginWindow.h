#ifndef LOGIN_H
#define LOGIN_H

#include <iostream>
#include <sstream>
#include <list>
#include "GameConfig.h"
#include "Button.h"
#include "Textbox.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class LoginWindow {
    private:
    Button *submit_btn, *back_btn;
    Textbox *username, *password;
    std::list<Textbox *> listTextbox;
    sf::Text *main;
public:
    LoginWindow(sf::Font *font);
    ~LoginWindow();

    void refresh();

    void update(sf::Vector2f mousePos);
    void typedOn(sf::Event ev);
    void drawTo(sf::RenderTarget &target);
    void setSelected(Textbox *textbox);

    bool submitPressed();
    bool backPressed();
};

#endif