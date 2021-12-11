#include "../include/Game.h"

Game::Game() {
    this->initVariables();
    this->initWindow();
}

Game::~Game() {
    delete this->window;
}

void Game::initVariables() {
    this->window = nullptr;
}

void Game::initWindow() {
    this->videoMode.width = 800;
    this->videoMode.height = 600;
    this->window = new sf::RenderWindow(this->videoMode, "My first game", sf::Style::Titlebar | sf::Style::Close);
}

const bool Game::running() const {
    return this->window->isOpen();
}

void Game::pollEvents() {
    //Event polling
    while(this->window->pollEvent(this->ev)) {
        switch (this->ev.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if (this->ev.key.code == sf::Keyboard::Escape)
                this->window->close();
            break;
        default:
            break;
        }
    }
}

void Game::update() {
    this->pollEvents();
}

void Game::render() {
    /*
        @return void
        - clear old frame
        - render objects
        - display frame in the window

        * Renders the game objects
    */

    this->window->clear(sf::Color(255, 0, 0, 255));
    
    //Draw game
    this->window->display();
}