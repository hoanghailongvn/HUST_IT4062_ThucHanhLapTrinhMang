#include "../include/LoginWindow.h"

using namespace std;

LoginWindow::LoginWindow(sf::Font *font) {
    this->main = new sf::Text();
    this->main->setString("Login");
    this->main->setFont(*font);
    this->main->setFillColor(sf::Color::White);
    this->main->setCharacterSize(80);
    auto textRect = this->main->getGlobalBounds();
    this->main->setOrigin(textRect.left + textRect.width/2.f, textRect.top + textRect.height/2.f);
    this->main->setPosition(screenWidth/2.f, 150);


    this->submit_btn = new Button(350, 450, 300, 100, font, "Submit", 36, sf::Color::Black, sf::Color::Magenta);
    this->back_btn = new Button(50, 550, 60, 20, font, "Back", 16, sf::Color::Black, sf::Color::Magenta);
    this->username = new Textbox(200, 250, font, "Username  : ", 26, sf::Color::White, true, usernameMaxLength);
    this->password = new Textbox(200, 300, font, "Password  : ", 26, sf::Color::White, false, passwordMaxLength);

    this->listTextbox.push_back(this->username);
    this->listTextbox.push_back(this->password);
}

LoginWindow::~LoginWindow() {
    delete this->main;
    delete this->submit_btn;
    delete this->back_btn;
    delete this->username;
    delete this->password;
}

void LoginWindow::refresh() {
    this->username->refresh();
    this->username->setSelected(true);
    this->password->refresh();
    this->password->setSelected(false);
}

void LoginWindow::update(sf::Vector2f mousePos) {
    this->submit_btn->update(mousePos);
    this->back_btn->update(mousePos);

    for(auto tbox: this->listTextbox) {
        if (tbox->isPressed(mousePos)) {
            this->setSelected(tbox);
            break;
        }
    }
}

void LoginWindow::typedOn(sf::Event ev) {
    this->username->typedOn(ev);
    this->password->typedOn(ev);
}

void LoginWindow::drawTo(sf::RenderTarget &target) {
    target.draw(*this->main);
    this->submit_btn->drawTo(target);
    this->back_btn->drawTo(target);
    this->username->drawTo(target);
    this->password->drawTo(target);
}

bool LoginWindow::submitPressed(char *message, int *fail_type) {
    if(this->submit_btn->isPressed()) {
        string s_username = this->username->getText();
        string s_password = this->password->getText();

        if (s_username.length() == 0 || s_password.length() == 0) {
            *fail_type = 1;
            return true;
        }

        rq_login rq;
        rq.username = s_username;
        rq.password = s_password;
        *fail_type = 0;

        struct_to_message(&rq, RQ_LOGIN, message);

        return true;
    }
    return false;
}

bool LoginWindow::backPressed() {
    return this->back_btn->isPressed();
}

void LoginWindow::setSelected(Textbox *textbox) {
    for (auto tbox: this->listTextbox) {
        if (tbox == textbox) {
            tbox->setSelected(true);
        } else {
            tbox->setSelected(false);
        }
    }
}