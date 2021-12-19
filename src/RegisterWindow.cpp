#include "../include/RegisterWindow.h"

using namespace std;

RegisterWindow::RegisterWindow(sf::Font *font) {
    this->main = new sf::Text();
    this->main->setString("Register");
    this->main->setFont(*font);
    this->main->setFillColor(sf::Color::White);
    this->main->setCharacterSize(80);
    auto textRect = this->main->getGlobalBounds();
    this->main->setOrigin(textRect.left + textRect.width/2.f, textRect.top + textRect.height/2.f);
    this->main->setPosition(screenWidth/2.f, 150);

    this->submit_btn = new Button(350, 450, 300, 100, font, "Submit", 36, sf::Color::Black, sf::Color::Magenta);
    this->back_btn = new Button(50, 550, 60, 20, font, "Back", 16, sf::Color::Black, sf::Color::Magenta);
    this->username = new Textbox(200, 250, font, "Username  : ", 26, sf::Color::White, true, usernameMaxLength);
    this->password_1 = new Textbox(200, 300, font, "Password  : ", 26, sf::Color::White, false, passwordMaxLength);
    this->password_2 = new Textbox(200, 350, font, "RePassword: ", 26, sf::Color::White, false, passwordMaxLength);

    this->listTextbox.push_back(this->username);
    this->listTextbox.push_back(this->password_1);
    this->listTextbox.push_back(this->password_2);
}

RegisterWindow::~RegisterWindow() {
    delete this->main;
    delete this->submit_btn;
    delete this->back_btn;
    delete this->username;
    delete this->password_1;
    delete this->password_2;
}

void RegisterWindow::refresh() {
    this->username->refresh();
    this->username->setSelected(true);
    this->password_1->refresh();
    this->password_1->setSelected(false);
    this->password_2->refresh();
    this->password_2->setSelected(false);
}

void RegisterWindow::update(sf::Vector2f mousePos) {
    this->submit_btn->update(mousePos);
    this->back_btn->update(mousePos);

    for(auto tbox: this->listTextbox) {
        if (tbox->isPressed(mousePos)) {
            this->setSelected(tbox);
            break;
        }
    }
}

void RegisterWindow::typedOn(sf::Event ev) {
    this->username->typedOn(ev);
    this->password_1->typedOn(ev);
    this->password_2->typedOn(ev);
}

void RegisterWindow::drawTo(sf::RenderTarget &target) {
    target.draw(*this->main);
    this->submit_btn->drawTo(target);
    this->back_btn->drawTo(target);
    this->username->drawTo(target);
    this->password_1->drawTo(target);
    this->password_2->drawTo(target);
}

/*
    @return true if pressed submit ||

    fail_type = 0: no problem,
    fail_type = 1: empty field,
    fail_type = 2: password != repassword
*/
bool RegisterWindow::submitPressed(char *message, int *fail_type) {
    if (this->submit_btn->isPressed()) {
        string s_username = this->username->getText();
        string s_password_1 = this->password_1->getText();
        string s_password_2 = this->password_2->getText();

        if (s_username.length() == 0 || s_password_1.length() == 0 || s_password_2.length() == 0) {
            *fail_type = 1;
            return true;
        }
        if (s_password_1.compare(s_password_2) != 0) {
            *fail_type = 2;
            return true;
        }

        rq_register rq;
        rq.username = s_username;
        rq.password = s_password_1;
        *fail_type = 0;

        struct_to_message(&rq, RQ_REGISTER, message);

        return true;
    } else {
        return false;
    }
}

bool RegisterWindow::backPressed() {
    return this->back_btn->isPressed();
}

void RegisterWindow::setSelected(Textbox *textbox) {
    for (auto tbox: this->listTextbox) {
        if (tbox == textbox) {
            tbox->setSelected(true);
        } else {
            tbox->setSelected(false);
        }
    }
}