#ifndef CREATEROOMWINDOW_H
#define CREATEROOMWINDOW_H

#include "LoginWindow.h"
#include <string>

class CreateRoomWindow {
protected:
    Button *submit_btn, *back_btn;
    sf::Text *main;
    Textbox *roomname;
    
public:
    CreateRoomWindow(sf::Font *font);
    ~CreateRoomWindow();

    void refresh();
    void update(sf::Vector2f mousePos);
    void typedOn(sf::Event ev);
    void drawTo(sf::RenderTarget &target);
    bool submitPressed(char *message, int *fail_type);
    bool backPressed();
    
};

#endif