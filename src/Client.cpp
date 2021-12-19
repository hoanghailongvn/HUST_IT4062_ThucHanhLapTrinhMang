#include "../include/Client.h"

using namespace std;

void Client::initNetwork()
{
    this->clientfd = socket(AF_INET, SOCK_STREAM, 0);

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

void Client::initNotification()
{
    this->notification = new Notification(this->font);
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
    this->initNotification();
}

Client::~Client()
{
    delete this->window;
    delete this->introWindow;
    delete this->registerWindow;
    delete this->font;
    delete this->notification;
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
            this->window->close();
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
                        this->rcv_rp_register();
                        break;
                    case 1:
                        this->notification->setText("Register Fail!!", 50, "Empty field", 20);
                        this->next_state = REGISTER;
                        break;
                    case 2:
                        this->notification->setText("Register Fail!!", 50, "Password not match!!", 20);
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
                if (loginWindow->submitPressed()) {
                    std::cout << "Press submit"
                            << "\n";
                }
            default:
                break;
            }

        case NOTIFICATION:
            if (ev.type == sf::Event::MouseButtonPressed) {
                this->state = this->next_state;
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
}

void Client::rcv_rp_register()
{
    int ret;
    ret = recv(this->clientfd, this->buff, BUFF_SIZE, 0);
    if (ret < 0) {
        perror("Error: ");
        exit(1);
    }

    struct rp_register rp = message_to_rp_register(this->buff);
    if (rp.accept) {
        this->notification->setText("Register Success!!", 50, "", 0);
        this->next_state = INTRO;
    } else {
        this->notification->setText("Register Fail!!", 50, rp.notification, 30);
        this->next_state = REGISTER;
    }
}

void Client::closeSocket()
{
    close(this->clientfd);
}