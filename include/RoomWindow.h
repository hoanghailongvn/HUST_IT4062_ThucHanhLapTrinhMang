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

class RoomWindow{
private:
    std::string name;
    std::vector<bool> ready;

    Button *back_btn, *ready_btn, *start_btn;
    std::vector <UserBox *> userBoxList;
    std::vector <std::string> userNameList;
    sf::Font *font;
    sf::Text *main;

    bool isHost;
public:
    RoomWindow(sf::Font *font);
    ~RoomWindow();

    void update(sf::Vector2f mousePos);
    void updateRoom(struct update_room input, UserClient *);
    void drawTo(sf::RenderTarget &target);

    std::string getName();
    void setName(std::string name);

    bool backPressed(char *message);
    bool readyPressed(char *message);
    bool startPressed(char *message);

    bool startable();
};

#endif 