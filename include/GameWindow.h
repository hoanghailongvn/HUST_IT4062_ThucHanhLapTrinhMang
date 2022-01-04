#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class GameWindow {
private:
    std::vector<int> x; // 0 - 5
    std::vector<int> y; // 0 - 4
    std::vector<int> point;
    std::vector<int> nb_word_done;

    int time_left; //60
    std::string target;
    
    std::vector<std::string> userNameList;
public:
    GameWindow(sf::Font *font);
    ~GameWindow();

    void setUsernameList(std::vector<std::string> userNameList);
    void updateGame(struct update_game rp);
    void updateTarget(struct update_target rp);
};


#endif