#ifndef ROOMWINDOW_H
#define ROOMWINDOW_H

#include "Room.h"
#include "Button.h"

#include <iostream>
#include <string>
#include <vector>
#include "GameConfig.h"
#include "Button.h"
#include "Textbox.h"
#include "Message.h"
#include "UserBox.h"
#include "UserClient.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class RoomWindow : public Room {
private:
    Button *back_btn, *ready_btn, *start_btn;
    std::vector <UserBox *> userBoxList;
    sf::Font *font;
    sf::Text *main;

public:
    RoomWindow(sf::Font *font);
    ~RoomWindow();

    void setupWindow(std::string name, std::vector<UserClient *> listUser, std::vector<bool> ready);

    void update(sf::Vector2f mousePos);
    void drawTo(sf::RenderTarget &target);

    bool backPressed(char *message);

};

#endif 