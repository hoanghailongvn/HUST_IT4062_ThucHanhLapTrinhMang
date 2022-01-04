#include "../include/GameWindow.h"
#include "../include/Message.h"
using namespace std;

GameWindow::GameWindow(sf::Font *font) {
    //Time
    this->time_text = new sf::Text();
    this->time_text->setCharacterSize(70);
    this->time_text->setPosition(screenWidth/2-30, 0);
    this->time_text->setFont(*font);

    //Initial point and name
    for (int i = 0; i < 4; i++) {
        this->point_text.push_back(new sf::Text());
        this->target_text.push_back(new sf::Text());

        this->point_text.back()->setCharacterSize(50);
        this->point_text.back()->setFont(*font);
        this->target_text.back()->setCharacterSize(30);
        this->target_text.back()->setFont(*font);
    }

    // board game

    char character = 'A';
    // y = 0; x = 1 | 5
    for(int i = 1; i < 6; i++) {
        this->character_box.push_back(new CharacterBox(base_x + box_size * i, base_y, box_size, font, character));
        character++;
    }
    
    // y = 1 -> 3
    for(int i = 1; i < 4; i++) {
        int y_pos = base_y + box_size*i; 
        for(int j = 0; j < 7; j++) {
            int x_pos = base_x + box_size*j;
            this->character_box.push_back(new CharacterBox(x_pos, y_pos, box_size, font, character));
            character++;
        }
    }

    //user character
    sf::Color listColor[4] = {sf::Color::Red, sf::Color::Blue, sf::Color::Green, sf::Color::Yellow};
    for(int i = 0; i < 4; i++) {
        this->avatar.push_back(new sf::CircleShape());
        this->user_character.push_back(new sf::CircleShape());
        
        this->avatar.back()->setFillColor(listColor[i]);
        this->user_character.back()->setFillColor(listColor[i]);

        this->avatar.back()->setRadius(radius);
        this->user_character.back()->setRadius(radius);

        this->avatar.back()->setOutlineColor(sf::Color::White);
        this->user_character.back()->setOutlineColor(sf::Color::White);

        this->avatar.back()->setOutlineThickness(2);
        this->user_character.back()->setOutlineThickness(2);
    }

    this->avatar.at(0)->setPosition(0 + 2, 0 + 2);
    this->avatar.at(1)->setPosition(screenWidth - radius * 2 - 2, 0 + 2);
    this->avatar.at(2)->setPosition(0 + 2, screenHeight - radius * 7 - 2);
    this->avatar.at(3)->setPosition(screenWidth - radius * 2 - 2, screenHeight - radius * 7 - 2);

    this->point_text.at(0)->setPosition(2, radius * 2);
    this->point_text.at(1)->setPosition(screenWidth - 20 - 2, radius * 2);
    this->point_text.at(2)->setPosition(2, screenHeight - radius * 5);
    this->point_text.at(3)->setPosition(screenWidth - 20 - 2, screenHeight - radius * 5);
    
}

GameWindow::~GameWindow(){}

void GameWindow::setNumberPlayer(int input) {
    this->nb_player = input;
}

void GameWindow::updateGame(struct update_game input) {
    this->x = input.x;
    this->y = input.y;
    for(int i = 0; i < this->x.size(); i++) {
        this->point_text.at(i)->setString(to_string(input.point.at(i)));
        this->user_character.at(i)->setPosition(this->user_character_base_pos_x.at(i) + box_size * this->x.at(i), this->user_character_base_pos_y.at(i) + box_size * this->y.at(i));
    }

    this->nb_word_done = input.nb_word_done;
    this->time_text->setString(to_string(input.time_left));

    for(int i = 0; i < this->nb_player; i++) {
        this->target_text.at(i)->setString(this->target.substr(this->nb_word_done.at(i)));
    }
    this->target_text.at(0)->setPosition(2, radius * 4 + 10);
    this->target_text.at(1)->setPosition(screenWidth - this->target_text.at(1)->getGlobalBounds().width - 2, radius * 4 + 10);
    this->target_text.at(2)->setPosition(2, screenHeight - radius * 3 + 10);
    this->target_text.at(3)->setPosition(screenWidth - this->target_text.at(3)->getGlobalBounds().width - 2, screenHeight - radius * 3 + 10);

}

void GameWindow::updateTarget(struct update_target input) {
    this->target = input.target;
}

void GameWindow::drawTo(sf::RenderTarget &target) {
    for(int i = 0; i < this->character_box.size(); i++) {
        this->character_box.at(i)->drawTo(target);
    }

    for(int i = 0; i < this->nb_player; i++) {
        target.draw(*this->point_text.at(i));
        target.draw(*this->user_character.at(i));
        target.draw(*this->avatar.at(i));
        target.draw(*this->target_text.at(i));
    }
    
    target.draw(*this->time_text);

}

void GameWindow::keyPressed(sf::Event ev, char *send_msg) {
    struct rq_action rq;

    switch (ev.key.code)
    {
    case sf::Keyboard::Space:
        rq.action = SPACE;
        break;
    
    case sf::Keyboard::Up:
        rq.action = UP;
        break;

    case sf::Keyboard::Down:
        rq.action = DOWN;
        break;

    case sf::Keyboard::Left:
        rq.action = LEFT;
        break;

    case sf::Keyboard::Right:
        rq.action = RIGHT;
        break;
    default:
        break;
    }

    struct_to_message(&rq, RQ_ACTION, send_msg);
}