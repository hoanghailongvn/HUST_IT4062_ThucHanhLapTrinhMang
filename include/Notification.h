#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <iostream>
#include <sstream>
#include <list>
#include "GameConfig.h"
#include "Button.h"
#include "Textbox.h"
#include "Message.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Notification {
private:
    sf::RectangleShape shape;
    sf::Text main;
    sf::Text sub;
public:
    Notification(sf::Font *font);
    ~Notification();

    void setText(std::string main, int main_size, std::string sub, int sub_size);
    void drawTo(sf::RenderTarget& target);

};

#endif 