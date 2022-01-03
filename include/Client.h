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
#include "../include/CreateRoomWindow.h"
#include "../include/JoinWindow.h"
#include "../include/RoomWindow.h"
#include "../include/UserClient.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

enum StateTypes
{
	INTRO,
    REGISTER,
    LOGIN,
    LOBBY,
    CREATEROOM,
    JOIN,
    ROOM,
    PLAY,
    NOTIFICATION,
};

class Client {
private: 

    //Network
    int clientfd, listenfd;
    struct sockaddr_in servAddr;

    UserClient *userClient;
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
    CreateRoomWindow *createRoomWindow;
    JoinWindow *joinWindow;
    RoomWindow *roomWindow;


    void initNetwork();
    void initVariables();
    void initWindow();
    void initIntroWindow();
    void initRegisterWindow();
    void initLoginWindow();
    void initLobbyWindow();
    void initNotification();
    void initCreateRoomWindow();
    void initJoinWindow();
    void initRoomWindow();
    void initFont();

public:
    Client();
    ~Client();

    UserClient* getUserClient();

    const bool running() const;

    void pollEvents();
    void updateMousePositions();
    void update();
    void render();

    //Network
    void run();
    void sendToServer(int fd, char *buff);
    void rcvFromServer(int fd, char *buff);

    void rp_register(char *rq_message);
    void rp_login(char *rq_message);
    void rp_logout(char *rq_message);
    void rp_createRoom(char *rq_message);
    void rp_joinRoom(char *rq_message);
    void rp_update_lobby(char *message);
    void rp_update_room(char *message);

    static void* routine1(void *);
    static void* routine2(void *); 
};

#endif


