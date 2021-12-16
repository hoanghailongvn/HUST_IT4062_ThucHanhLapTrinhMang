#include "../include/Window.h"

void Window::initVariables()
{
    this->state = INTRO;
}

void Window::initWindow()
{
    this->videoMode.width = screenWidth;
    this->videoMode.height = screenHeight;
    this->window = new sf::RenderWindow(this->videoMode, titleGame, sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
    this->window->setVerticalSyncEnabled(true);
}

void Window::initIntroWindow() {
    this->introWindow = new IntroWindow(this->font);
}

void Window::initRegisterWindow() {
    this->registerWindow = new RegisterWindow(this->font);
}

void Window::initLoginWindow() {
    this->loginWindow = new LoginWindow(this->font);
}

void Window::initFont() {
    this->font = new sf::Font();
    this->font->loadFromFile(fontPerfectDosPath);
}

Window::Window() {
    this->initFont();
    this->initVariables();
    this->initWindow();
    this->initIntroWindow();
    this->initRegisterWindow();
    this->initLoginWindow();
}

Window::~Window() {
    delete this->window;
    delete this->introWindow;
    delete this->registerWindow;
    delete this->font;
}

const bool Window::running() const
{
    return this->window->isOpen();
}

void Window::pollEvents()
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

void Window::updateMousePositions()
{
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Window::update()
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

void Window::render()
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