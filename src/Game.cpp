// #include "../include/Game.h"

// //Init variables
// void Game::initVariables()
// {
//     this->window = nullptr;

//     // Game logic
//     this->endGame = false;
//     this->points = 0;
//     this->health = 10;
//     this->enemySpawnTimerMax = 10.f;
//     this->enemySpawnTimer = this->enemySpawnTimerMax;
//     this->maxEnemies = 5;
//     this->mouseHeld = false;
// }

// void Game::initWindow()
// {
//     this->videoMode.width = 800;
//     this->videoMode.height = 600;
//     this->window = new sf::RenderWindow(this->videoMode, "My first game", sf::Style::Titlebar | sf::Style::Close);
//     this->window->setFramerateLimit(60);
// }

// void Game::initEnemies()
// {
//     this->enemy.setPosition(sf::Vector2f(10.f, 10.f));
//     this->enemy.setSize(sf::Vector2f(100.f, 100.f));
//     this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
//     this->enemy.setFillColor(sf::Color::Cyan);
//     this->enemy.setOutlineColor(sf::Color::Green);
//     this->enemy.setOutlineThickness(1.f);
// }

// //Constructor and Deconstructor
// Game::Game()
// {
//     this->initVariables();
//     this->initWindow();
//     this->initEnemies();
// }

// Game::~Game()
// {
//     delete this->window;
// }


// // Accessor
// const bool Game::running() const
// {
//     return this->window->isOpen();
// }

// const bool Game::getEndGame() const {
//     return this->endGame;
// }

// void Game::pollEvents()
// {
//     // Event polling
//     while (this->window->pollEvent(this->ev)) {
//         switch (this->ev.type) {
//         case sf::Event::Closed:
//             this->window->close();
//             break;
//         case sf::Event::KeyPressed:
//             if (this->ev.key.code == sf::Keyboard::Escape)
//                 this->window->close();
//             break;
//         default:
//             break;
//         }
//     }
// }

// void Game::update()
// {
//     this->pollEvents();

//     if (!this->endGame) {
//         this->updateMousePositions();
//         this->updateEnemies();
//     }
//     if (this->health <= 0) {
//         this->endGame = true;
//     }
    
// }

// void Game::render()
// {
//     /*
//         @return void
//         - clear old frame
//         - render objects
//         - display frame in the window

//         * Renders the game objects
//     */

//     this->window->clear();

//     // Draw game
//     this->renderEnemies();

//     this->window->display();
// }


// void Game::updateMousePositions()
// {
//     /*
//     @ return void

//     Updates the mouse positions:
//         * Mouse position relative to window (Vector2i)
//     */
//     this->mousePosWindow = sf::Mouse::getPosition(*this->window);
//     this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
// }

// void Game::updateEnemies()
// {
//     if (this->enemies.size() < this->maxEnemies) {
//         if (this->enemySpawnTimer >= this->enemySpawnTimerMax) {
//             this->spawnEnemy();
//             this->enemySpawnTimer = 0.f;
//         } else {
//             this->enemySpawnTimer += 1;
//         }
//     }

//     for (int i = 0; i < this->enemies.size(); i++) {
//         bool deleted = false;

//         this->enemies[i].move(0.f, 1.f);

//         if (this->enemies[i].getPosition().y > this->window->getSize().y) {
//             this->enemies.erase(this->enemies.begin() + i);
//             this->health -= 1;
//             std::cout << "Health: " << this->health << std::endl;
//         }
//     }
    
//     if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
//         if (this->mouseHeld == false) {
//             this->mouseHeld = true;

//             bool deleted = false;
//             for (size_t i = 0; i < this->enemies.size() && deleted == false; i++) {
//                 if (this->enemies[i].getGlobalBounds().contains(this->mousePosView)) {
//                     //Delete enemy
//                     deleted = true;
//                     this->enemies.erase(this->enemies.begin() + i);

//                     //Gain points
//                     this->points += 10.f;
//                     std::cout << "points: " << this->points << std::endl;

//                 }
//             }
//         }
//     } else {
//         this->mouseHeld = false;
//     }
// }

// void Game::renderEnemies()
// {
//     for (auto& e : this->enemies) {
//         this->window->draw(e);
//     }
// }

// void Game::spawnEnemy()
// {
//     /*
//         @return void

//         Spawns enemies and sets their colors and positions.
//         -Sets a random position.
//         -Sets a random color.
//         -Add to vector
//     */
//     this->enemy.setPosition(
//         rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x),
//         0);

//     this->enemy.setFillColor(sf::Color::Green);

//     this->enemies.push_back(this->enemy);
// }