#ifndef LOBBYWINDOW_H
#define LOBBYWINDOW_H

#include <iostream>
#include <sstream>
#include <list>
#include "GameConfig.h"
#include "Button.h"
#include "Textbox.h"
#include "Message.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class LobbyWindow {
private:
    Button *logout_btn;
    // Textbox *username, *password_1, *password_2;
    // std::list<Textbox *> listTextbox;
    sf::Text *main;
    sf::Text *userName;
public:
    LobbyWindow(sf::Font *font);
    ~LobbyWindow();

    void setUsername(std::string username);

    void refresh();

    void update(sf::Vector2f mousePos);
    void drawTo(sf::RenderTarget &target);

    // bool submitPressed(char *message, int *fail_type);
    bool logoutPressed(char *message);

};

#endif