#ifndef GAME_H
#define GAME_H

#include <ctime>
#include <iostream>
#include <vector>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

enum Action {UP, DOWN, LEFT, RIGHT, SPACE};

class Game {
private:

    // Game logic
    bool endGame;
    unsigned points;
    unsigned health;
    float enemySpawnTimer;
    float enemySpawnTimerMax;
    int maxEnemies;
    bool mouseHeld;

    //Game objects
    std::vector<sf::RectangleShape> enemies;
    sf::RectangleShape enemy;

    //Private functions
    void initVariables();
    void initWindow();
    void initEnemies();

public:
    Game();
    virtual ~Game();

    // Accessors
    const bool running() const;
    const bool getEndGame() const;

    // Functions
    void spawnEnemy();
    void pollEvents();
    void updateMousePositions();
    void update();
    void updateEnemies();
    void renderEnemies();
    void render();
};

#endif