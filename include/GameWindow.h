#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "CharacterBox.h"
#include "GameConfig.h"

class GameWindow {
private:
    int box_size = 100;
    int base_x = 150;
    int base_y = 100;
    int radius = 20;

    int nb_player = 0;

    std::vector<int> x; // 0 - 5
    std::vector<int> y; // 0 - 4
    std::vector<int> nb_word_done;

    std::string target;
    
    //graphic
    std::vector<sf::Text *> point_text;
    std::vector<sf::Text *> target_text;
    std::vector<CharacterBox *> character_box;
    std::vector<sf::CircleShape *> avatar;
    std::vector<sf::CircleShape *> user_character;
    sf::Text *time_text;

    std::vector<int> user_character_base_pos_x{this->base_x + 2, this->base_x + this->box_size - radius * 2 - 2,
                            this->base_x + 2, this->base_x + this->box_size - radius * 2 - 2};
    std::vector<int> user_character_base_pos_y{this->base_y + 2, this->base_y + 2,
                            this->base_y + box_size - radius * 2 - 2, this->base_y + box_size - radius * 2 - 2};

public:
    GameWindow(sf::Font *font);
    ~GameWindow();

    void setNumberPlayer(int);
    void updateGame(struct update_game rp);
    void updateTarget(struct update_target rp);
    void keyPressed(sf::Event ev, char *send_msg);
    int getNbPlayer();

    void drawTo(sf::RenderTarget &target);
};


#endif