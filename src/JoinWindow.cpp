#include "../include/JoinWindow.h"

using namespace std;

JoinWindow::JoinWindow(sf::Font *font) {
    this->main = new sf::Text();
    this->main->setString("Join Room");
    this->main->setFont(*font);
    this->main->setFillColor(sf::Color::White);
    this->main->setCharacterSize(80);
    auto textRect = this->main->getGlobalBounds();
    this->main->setOrigin(textRect.left + textRect.width/2.f, textRect.top + textRect.height/2.f);
    this->main->setPosition(screenWidth/2.f, 150);

    this->submit_btn = new Button(350, 450, 300, 100, font, "Submit", 36, sf::Color::Black, sf::Color::Magenta);
    this->back_btn = new Button(50, 550, 60, 20, font, "Back", 16, sf::Color::Black, sf::Color::Magenta);
    this->roomname = new Textbox(200, 250, font, "Room Name: ", 26, sf::Color::White, true, usernameMaxLength);
}

JoinWindow::~JoinWindow() {
    delete this->submit_btn;
    delete this->back_btn;
    delete this->main;
    delete this->roomname;

}

void JoinWindow::refresh() {
    this->roomname->refresh();
    this->roomname->setSelected(true);
}

void JoinWindow::update(sf::Vector2f mousePos) {
    this->submit_btn->update(mousePos);
    this->back_btn->update(mousePos);
}

void JoinWindow::typedOn(sf::Event ev) {
    this->roomname->typedOn(ev);
}

void JoinWindow::drawTo(sf::RenderTarget &target) {
    target.draw(*this->main);
    this->submit_btn->drawTo(target);
    this->back_btn->drawTo(target);
    this->roomname->drawTo(target);
}

bool JoinWindow::submitPressed(char *message, int *fail_type) {
    if(this->submit_btn->isPressed()) {
        string s_roomname = this->roomname->getText();

        if (s_roomname.length() == 0) {
            *fail_type = 1;
            return true;
        }

        rq_join_room rq;
        rq.room_name = s_roomname;
        *fail_type = 0;

        struct_to_message(&rq, RQ_JOIN_ROOM, message);

        return true;
    }
    return false;
}

bool JoinWindow::backPressed() {
    return this->back_btn->isPressed();
}