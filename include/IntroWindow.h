#ifndef INTRO_H
#define INTRO_H

#include "Button.h"

class IntroWindow {
private:
    Button *register_btn, *login_btn;
public:
    IntroWindow(sf::Font *font);
    ~IntroWindow();

    void update(sf::Vector2f mousePos);
    void drawTo(sf::RenderTarget &target);
};

#endif 