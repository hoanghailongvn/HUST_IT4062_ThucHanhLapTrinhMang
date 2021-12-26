#include "../include/Client.h"

using namespace std;

void Client::initNetwork()
{
    this->clientfd = socket(AF_INET, SOCK_STREAM, 0);
    this->listenfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&this->servAddr, sizeof(this->servAddr));
    this->servAddr.sin_family = AF_INET;
    this->servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    this->servAddr.sin_port = htons(SERVER_PORT);
}

void Client::initVariables()
{
    this->state = INTRO;
}

void Client::initWindow()
{
    this->videoMode.width = screenWidth;
    this->videoMode.height = screenHeight;
    this->window = new sf::RenderWindow(this->videoMode, titleGame, sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
    this->window->setVerticalSyncEnabled(true);
}

void Client::initIntroWindow()
{
    this->introWindow = new IntroWindow(this->font);
}

void Client::initRegisterWindow()
{
    this->registerWindow = new RegisterWindow(this->font);
}

void Client::initLoginWindow()
{
    this->loginWindow = new LoginWindow(this->font);
}

void Client::initLobbyWindow() {
    this->lobbyWindow = new LobbyWindow(this->font);
}

void Client::initNotification()
{
    this->notification = new Notification(this->font);
}

void Client::initCreateRoomWindow() {
    this->createRoomWindow = new CreateRoomWindow(this->font);
}

void Client::initRoomWindow() {
    this->roomWindow = new RoomWindow(this->font);
}

void Client::initFont()
{
    this->font = new sf::Font();
    this->font->loadFromFile(fontPerfectDosPath);
}

Client::Client()
{
    this->initNetwork();
    this->communicate();

    this->initFont();
    this->initVariables();
    this->initWindow();
    this->initIntroWindow();
    this->initRegisterWindow();
    this->initLoginWindow();
    this->initLobbyWindow();
    this->initNotification();
    this->initCreateRoomWindow();
    this->initRoomWindow();
}

Client::~Client()
{
    delete this->window;
    delete this->font;
    delete this->introWindow;
    delete this->registerWindow;
    delete this->loginWindow;
    delete this->lobbyWindow;
    delete this->notification;
    delete this->createRoomWindow;
}

const bool Client::running() const
{
    return this->window->isOpen();
}

void Client::pollEvents()
{
    // Event polling
    while (this->window->pollEvent(this->ev)) {
        if (this->ev.type == sf::Event::Closed) {
            rq_exit temp;
            struct_to_message(&temp, RQ_EXIT, this->buff);
            this->sendToServer();
            this->window->close();
            exit(0);
            continue;
        }

        switch (this->state) {
        case INTRO:
            switch (ev.type) {
            case sf::Event::MouseButtonPressed:
                if (introWindow->registerPressed()) {
                    this->state = REGISTER;
                    this->registerWindow->refresh();
                }
                if (introWindow->loginPressed()) {
                    this->state = LOGIN;
                    this->loginWindow->refresh();
                }
                break;

            default:
                break;
            }
            break;
        case REGISTER:
            switch (ev.type) {
            case sf::Event::TextEntered:
                this->registerWindow->typedOn(ev);
                break;

            case sf::Event::MouseButtonPressed:
                if (registerWindow->backPressed()) {
                    this->state = INTRO;
                }
                int fail_type;
                if (registerWindow->submitPressed(this->buff, &fail_type)) {
                    switch (fail_type) {
                    case 0:
                        this->sendToServer();
                        this->rcvFromServer();
                        this->rp_register();
                        break;
                    case 1:
                        this->notification->setText("Register Fail!!", 50, "Empty field", 30);
                        this->next_state = REGISTER;
                        break;
                    case 2:
                        this->notification->setText("Register Fail!!", 50, "Password not match!!", 30);
                        this->next_state = REGISTER;
                        break;
                    default:
                        break;
                    }

                    this->state = NOTIFICATION;
                }
            default:
                break;
            }
            break;
        case LOGIN:
            switch (ev.type) {
            case sf::Event::TextEntered:
                this->loginWindow->typedOn(ev);
                break;

            case sf::Event::MouseButtonPressed:
                if (loginWindow->backPressed()) {
                    this->state = INTRO;
                }
                int fail_type;
                if (loginWindow->submitPressed(this->buff, &fail_type)) {
                    if(fail_type == 0) {
                        this->sendToServer();
                        this->rcvFromServer();
                        this->rp_login();
                    } else if (fail_type == 1) {
                        this->notification->setText("Login Fail!!", 50, "Empty field.", 30);
                        this->next_state = LOGIN;
                    }
                    this->state = NOTIFICATION;
                }
                break;
            default:
                break;
            }
            break;
        case NOTIFICATION:
            if (ev.type == sf::Event::MouseButtonPressed) {
                this->state = this->next_state;
            }
            break;
        case LOBBY:
            switch (ev.type)
            {
            case sf::Event::MouseButtonPressed:
                if (this->lobbyWindow->logoutPressed(this->buff)) {
                    this->sendToServer();
                    this->rcvFromServer();
                    this->rp_logout();
                    this->next_state = INTRO;
                    this->state = NOTIFICATION;
                }
                if (this->lobbyWindow->createRoomPressed()) {
                    this->state = CREATEROOM;
                    this->createRoomWindow->refresh();
                }
                break;
            
            default:
                break;
            }
            break;
        case CREATEROOM:
            switch (ev.type)
            {
            case sf::Event::TextEntered:
                this->createRoomWindow->typedOn(ev);
                break;
            
            case sf::Event::MouseButtonPressed:
                if (this->createRoomWindow->backPressed()) {
                    this->state = LOBBY;
                }
                int fail_type;
                if (createRoomWindow->submitPressed(this->buff, &fail_type)) {
                    if(fail_type == 0) {
                        this->sendToServer();
                        this->rcvFromServer();
                        this->rp_createRoom();
                    } else if (fail_type == 1) {
                        this->notification->setText("Create Room Fail!!", 50, "Empty field.", 30);
                        this->state = NOTIFICATION;
                        this->next_state = CREATEROOM;
                    }
                }
                break;
            }
            break;
        case ROOM:
            switch (ev.type)
            {
            case sf::Event::MouseButtonPressed:
                if (this->roomWindow->backPressed(this->buff)) {
                    this->sendToServer();
                    this->state = LOBBY;
                }

                break;
            }
        default:
            break;
        }
    }
}

void Client::updateMousePositions()
{
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Client::update()
{
    this->pollEvents();

    this->updateMousePositions();

    switch (this->state) {
    case INTRO:
        this->introWindow->update(this->mousePosView);
        break;
    case REGISTER:
        this->registerWindow->update(this->mousePosView);
        break;
    case LOGIN:
        this->loginWindow->update(this->mousePosView);
        break;
    case LOBBY:
        this->lobbyWindow->update(this->mousePosView);
        break;
    case CREATEROOM:
        this->createRoomWindow->update(this->mousePosView);
        break;
    case ROOM:
        this->roomWindow->update(this->mousePosView);
        break;
    default:
        break;
    }
}

void Client::render()
{
    this->window->clear();

    // Draw game
    switch (this->state) {
    case INTRO:
        this->introWindow->drawTo(*this->window);
        break;

    case REGISTER:
        this->registerWindow->drawTo(*this->window);
        break;

    case LOGIN:
        this->loginWindow->drawTo(*this->window);
        break;

    case NOTIFICATION:
        this->notification->drawTo(*this->window);
        break;

    case LOBBY:
        this->lobbyWindow->drawTo(*this->window);
        break;
    case CREATEROOM:
        this->createRoomWindow->drawTo(*this->window);
        break;
    case ROOM:
        this->roomWindow->drawTo(*this->window);
        break;
    default:
        break;
    }

    this->window->display();
}

void Client::communicate()
{
    if (connect(this->clientfd, (sockaddr*)&this->servAddr, sizeof(this->servAddr))) {
        perror("Error: ");
        exit(1);
    }
}

void Client::sendToServer()
{
    int ret;
    ret = send(this->clientfd, this->buff, strlen(this->buff), 0);
    if (ret < 0) {
        perror("Error: ");
        exit(1);
    }
    cout << "\nSend: " << "\n{\n" << this->buff << "\n}\n";
}
void Client::rcvFromServer() {
    int ret;
    ret = recv(this->clientfd, this->buff, BUFF_SIZE, 0);
    if (ret < 0) {
        perror("Error: ");
        exit(1);
    }
    this->buff[ret] = '\0';
    cout << "\nReceiv: " << "\n{\n" << this->buff << "\n}\n";
}

void Client::rp_register()
{
    struct rp_register rp = message_to_rp_register(this->buff);
    if (rp.accept) {
        this->notification->setText("Register Success!!", 50, "", 0);
        this->next_state = INTRO;
    } else {
        this->notification->setText("Register Fail!!", 50, rp.notification, 30);
        this->next_state = REGISTER;
    }
}

void Client::rp_login() {
    struct rp_login rp = message_to_rp_login(this->buff);
    if (rp.accept) {
        this->notification->setText("Login Success!!", 50, "", 0);
        this->next_state = LOBBY;
        this->userName = rp.username;
        this->lobbyWindow->setUsername(this->userName);
    } else {
        this->notification->setText("Login Fail!!", 50, rp.notification, 30);
        this->next_state = LOGIN;
    }

}

void Client::rp_logout() {
    struct rp_logout rp = message_to_rp_logout(this->buff);
    if (rp.accept) {
        this->notification->setText("Logout Success!!", 50, "", 0);
        this->next_state = INTRO;
        this->userName = "";
    } else {
        this->notification->setText("Logout Fail!!", 50, rp.notification, 30);
        this->next_state = LOBBY;
    }
}

void Client::rp_createRoom() {
    struct rp_create_room rp = message_to_rp_create_room(this->buff);
    if (rp.accept) {
        this->state = ROOM;
        this->roomWindow->setupWindow(rp.roomname, vector<string>{this->userName}, vector<bool>{false});

    } else {
        this->notification->setText("Create Room Fail!!", 50, rp.notification, 30);
        this->state = NOTIFICATION;
        this->next_state = LOBBY;
    }
}

void Client::closeSocket()
{
    close(this->clientfd);
    close(this->listenfd);
}