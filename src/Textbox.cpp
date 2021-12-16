#include "../include/Textbox.h"

Textbox::Textbox() {
    this->isSelected = false;
    this->hasLimit = false;
}

Textbox::~Textbox() {}

Textbox::Textbox(int size, sf::Color color, bool sel) {
    this->textbox.setCharacterSize(size);
    this->textbox.setFillColor(color);
    this->isSelected = sel;
    if (sel) {
        this->textbox.setString("_");
    } else {
        this->textbox.setString("");
    }
}

void Textbox::setFont(sf::Font& font) {
    this->textbox.setFont(font);
}

void Textbox::setPosition(sf::Vector2f pos) {
    this->textbox.setPosition(pos);
}

void Textbox::setLimit(bool ToF) {
    this->hasLimit = ToF;
}

void Textbox::setLimit(bool ToF, int lim) {
    this->hasLimit = ToF;
    this->limit = lim;
}

void Textbox::setSelected(bool sel) {
    this->isSelected = sel;
    if (!sel) {
        std::string t = this->text.str();
        std::string newT = "";
        for (int i = 0; i < t.length() - 1; i++) {
            newT += t[i];
        }
        textbox.setString(newT);
    }
}

std::string Textbox::getText() {
    return this->text.str();
}

void Textbox::drawTo(sf::RenderWindow &window) {
    window.draw(this->textbox);
}

void Textbox::typedOn(sf::Event input) {
    if(this->isSelected) {
        int charTyped = input.text.unicode;
        if(charTyped < 128) {
            if (hasLimit) {
                if(this->text.str().length() <= limit) {
                    this->inputLogic(charTyped);
                } else if(charTyped == DELETE_KEY) {
                    this->deleteLastChar();
                }
            } else {
                this->inputLogic(charTyped);
            }
        }
    }
}

void Textbox::inputLogic(int charTyped) {
    if (charTyped != DELETE_KEY && charTyped != ESCAPE_KEY && charTyped != ENTER_KEY){
        text << static_cast<char>(charTyped);
    } else if (charTyped == DELETE_KEY) {
        if (text.str().length() > 0) {
            this->deleteLastChar();
        }
    }
    textbox.setString(text.str() + "_");
}

void Textbox::deleteLastChar() {
    std::string t = this->text.str();
    std::string newT = "";
    for (int i = 0; i < t.length() - 1; i++) {
        newT += t[i];
    }
    this->text.str("");
    this->text << newT;

    textbox.setString(this->text.str());
}