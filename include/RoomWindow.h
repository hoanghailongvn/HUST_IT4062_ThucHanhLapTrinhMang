#ifndef ROOMWINDOW_H
#define ROOMWINDOW_H

#include "Room.h"
#include "Button.h"

#include <iostream>
#include <string>
#include "GameConfig.h"
#include "Button.h"
#include "Textbox.h"
#include "Message.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class RoomWindow {
private:
    Room room;
    Button *back_btn, *ready_start_btn;
    

public:
    RoomWindow();
    ~RoomWindow();

    void update(sf::Vector2f mousePos);
    void drawTo(sf::RenderTarget &target);

};

#endif 