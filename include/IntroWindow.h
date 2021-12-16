#ifndef INTRO_H
#define INTRO_H

#include <iostream>
#include <ctime>
#include <sstream>
#include "GameConfig.h"
#include "Button.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class IntroWindow {
private:
    Button *register_btn, *login_btn;
public:
    IntroWindow(sf::Font *font);
    ~IntroWindow();

    void update(sf::Vector2f mousePos);
    void drawTo(sf::RenderTarget &target);

    bool registerPressed();
    bool loginPressed();
};

#endif 