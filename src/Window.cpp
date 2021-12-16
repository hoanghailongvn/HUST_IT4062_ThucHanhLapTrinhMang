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
    this->introWindow = new IntroWindow(this->fontArcade);
}

void Window::initFont() {
    this->fontArcade = new sf::Font();
    this->fontArcade->loadFromFile(fontArcadePath);
}

Window::Window() {
    this->initFont();
    this->initVariables();
    this->initWindow();
    this->initIntroWindow();
}

Window::~Window() {
    delete this->window;
    delete this->introWindow;
    delete this->fontArcade;
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
    
    default:
        break;
    }

    this->window->display();
}