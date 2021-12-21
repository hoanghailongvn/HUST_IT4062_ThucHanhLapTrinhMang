#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <stdio.h>
#include <string.h>
#include "GameConfig.h"
#include "Message.h"
#include "User.h"

#include <arpa/inet.h> // in_addr
#include <sys/socket.h> // socklen_t
#include <netdb.h> //dns
#include <unistd.h> //close

#include "../include/Button.h"
#include "../include/IntroWindow.h"
#include "../include/RegisterWindow.h"
#include "../include/LoginWindow.h"
#include "../include/Notification.h"
#include "../include/LobbyWindow.h"

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

    std::string userName;
    // Variables

    // Window
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event ev;
    StateTypes state, next_state;

    // Mouse position
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    sf::Font *font;

    // windows
    IntroWindow *introWindow;
    RegisterWindow *registerWindow;
    LoginWindow *loginWindow;
    LobbyWindow *lobbyWindow;
    Notification *notification;


    void initNetwork();
    void initVariables();
    void initWindow();
    void initIntroWindow();
    void initRegisterWindow();
    void initLoginWindow();
    void initLobbyWindow();
    void initNotification();
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
    void rcvFromServer();

    void rp_register();
    void rp_login();
    void rp_logout();

    void closeSocket();
};

#endif


