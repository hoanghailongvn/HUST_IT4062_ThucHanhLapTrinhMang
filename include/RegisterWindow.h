#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <iostream>
#include <sstream>
#include <list>
#include "GameConfig.h"
#include "Button.h"
#include "Textbox.h"
#include "Message.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

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

    bool submitPressed(char *message, int *fail_type);
    bool backPressed();
};

#endif