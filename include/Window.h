#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include "GameConfig.h"
#include "../include/Button.h"
#include "../include/IntroWindow.h"
#include "../include/RegisterWindow.h"
#include "../include/LoginWindow.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

enum StateTypes
{
	INTRO,
    REGISTER,
    LOGIN,
    LOBBY,
    ROOM,
    PLAY,
    NOTIFICATION,
};

class Window {
private:
    // Variables
    // Window
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event ev;
    StateTypes state;

    // Mouse position
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    sf::Font *font;

    // windows
    IntroWindow *introWindow;
    RegisterWindow *registerWindow;
    LoginWindow *loginWindow;

    void initVariables();
    void initWindow();
    void initIntroWindow();
    void initRegisterWindow();
    void initLoginWindow();
    void initFont();

public:
    Window();
    ~Window();

    const bool running() const;

    void pollEvents();
    void updateMousePositions();
    void update();
    void render();
};

#endif