#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <stdio.h>
#include <string.h>
#include "GameConfig.h"
#include "Message.h"

#include <arpa/inet.h> // in_addr
#include <sys/socket.h> // socklen_t
#include <netdb.h> //dns
#include <unistd.h> //close

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

class Client {
private: 

    //Network
    int clientfd;
    char buff[BUFF_SIZE + 1];
    struct sockaddr_in servAddr;
    // Variables

    // Window
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event ev;
    StateTypes state, previous_state;

    // Mouse position
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    sf::Font *font;

    // windows
    IntroWindow *introWindow;
    RegisterWindow *registerWindow;
    LoginWindow *loginWindow;

    void initNetwork();
    void initVariables();
    void initWindow();
    void initIntroWindow();
    void initRegisterWindow();
    void initLoginWindow();
    void initFont();

public:
    Client();
    ~Client();

    const bool running() const;

    void pollEvents();
    void updateMousePositions();
    void update();
    void render();

    //Network
    void communicate();
    void run();
    void sendToServer();

    void rcv_rp_register();

    void closeSocket();
};

#endif


