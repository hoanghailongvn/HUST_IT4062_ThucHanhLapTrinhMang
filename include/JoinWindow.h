#ifndef JOINWINDOW_H
#define JOINWINDOW_H

#include <iostream>
#include <sstream>
#include <list>
#include <string>
#include "GameConfig.h"
#include "Button.h"
#include "Textbox.h"
#include "Message.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class JoinWindow {
protected:
    Button *submit_btn, *back_btn;
    sf::Text *main;
    Textbox *roomname;
    
public:
    JoinWindow(sf::Font *font);
    ~JoinWindow();

    void refresh();
    void update(sf::Vector2f mousePos);
    void typedOn(sf::Event ev);
    void drawTo(sf::RenderTarget &target);
    bool submitPressed(char *message, int *fail_type);
    bool backPressed();
    
};

#endif