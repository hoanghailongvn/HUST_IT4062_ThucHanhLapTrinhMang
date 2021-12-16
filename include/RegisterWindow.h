#ifndef REGISTER_H
#define REGISTER_H

#include <iostream>
#include <ctime>
#include <sstream>
#include <list>
#include "GameConfig.h"
#include "Button.h"
#include "Textbox.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

struct RegisterForm {
    char username[usernameMaxLength + 1];
    char password_1[passwordMaxLength + 1];
    char password_2[passwordMaxLength + 1];
};

class RegisterWindow {
    private:
    Button *submit_btn, *back_btn;
    Textbox *username, *password_1, *password_2;
    std::list<Textbox *> listTextbox;
    sf::Text *main;
public:
    RegisterWindow(sf::Font *font);
    ~RegisterWindow();

    void refresh();

    void update(sf::Vector2f mousePos);
    void typedOn(sf::Event ev);
    void drawTo(sf::RenderTarget &target);
    void setSelected(Textbox *textbox);

    bool submitPressed();
    bool backPressed();
};

#endif