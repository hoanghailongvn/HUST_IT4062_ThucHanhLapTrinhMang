#include "../include/Client.h"

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

void Client::initIntroWindow() {
    this->introWindow = new IntroWindow(this->font);
}

void Client::initRegisterWindow() {
    this->registerWindow = new RegisterWindow(this->font);
}

void Client::initLoginWindow() {
    this->loginWindow = new LoginWindow(this->font);
}

void Client::initFont() {
    this->font = new sf::Font();
    this->font->loadFromFile(fontPerfectDosPath);
}

Client::Client() {
    this->initFont();
    this->initVariables();
    this->initWindow();
    this->initIntroWindow();
    this->initRegisterWindow();
    this->initLoginWindow();
}

Client::~Client() {
    delete this->window;
    delete this->introWindow;
    delete this->registerWindow;
    delete this->font;
}

const bool Client::running() const
{
    return this->window->isOpen();
}

void Client::pollEvents()
{
    // Event polling
    while (this->window->pollEvent(this->ev)) {
        switch (this->ev.type) {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::TextEntered:
            switch (this->state)
            {
            case REGISTER:
                this->registerWindow->typedOn(ev);
                break;
            
            case LOGIN:
                this->loginWindow->typedOn(ev);
                break;
            default:
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

    switch (this->state)
    {
    case INTRO:
        this->introWindow->update(this->mousePosView);
        if(introWindow->registerPressed()) {
            this->state = REGISTER;
            this->registerWindow->refresh();
        } 
        if(introWindow->loginPressed()) {
            this->state = LOGIN;
            this->loginWindow->refresh();
        }
        break;
    case REGISTER:
        this->registerWindow->update(this->mousePosView);
        if(registerWindow->backPressed()) {
            this->state = INTRO;
        }
        if(registerWindow->submitPressed()) {

            std::cout << "Press submit" << "\n";
        }
        break;
    case LOGIN:
        this->loginWindow->update(this->mousePosView);
        if(loginWindow->backPressed()) {
            this->state = INTRO;
        }
        if(loginWindow->submitPressed()) {
            std::cout << "Press submit" << "\n";
        }
        break;
    default:
        break;
    }
}

void Client::render()
{
    this->window->clear();

    // Draw game
    switch (this->state)
    {
    case INTRO:
        this->introWindow->drawTo(*this->window);
        break;
    
    case REGISTER:
        this->registerWindow->drawTo(*this->window);
        break;

    case LOGIN:
        this->loginWindow->drawTo(*this->window);
        break;
    default:
        break;
    }

    this->window->display();
}


// #include "../include/Client.h"

// Client::Client() {
//     this->clientfd = socket(AF_INET, SOCK_STREAM, 0);

//     bzero(&this->servAddr, sizeof(this->servAddr));
//     this->servAddr.sin_family = AF_INET;
//     this->servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
//     this->servAddr.sin_port = htons(SERVER_PORT);
// }

// Client::~Client() {

// }

// void Client::communicate() {
//     if (connect(this->clientfd, (sockaddr *)&this->servAddr, sizeof(this->servAddr))) {
//         perror("Error: ");
//         exit(1);
//     }
// }



        
//     // //Step 5: Communicate with server
//     // int ret;
//     // // Send message
//     // printf("Send to server: ");
//     // fgets(this->buff, BUFF_SIZE, stdin);
//     // ret = send(this->clientfd, this->buff, strlen(this->buff), 0);
//     // if (ret < 0) {
//     //     perror("Error: ");
//     //     exit(1);
//     // }

//     // //Receive echo message
//     // ret = recv(this->clientfd, buff, BUFF_SIZE, 0);
//     // if (ret < 0) {
//     //     perror("Error");
//     //     exit(1);
//     // }
//     // printf("Receive from server: %s\n", buff);
// }

// void Client::closeSocket() {
//     close(this->clientfd);
// }