#include "../include/Textbox.h"

Textbox::Textbox(float x, float y, sf::Font* font, std::string textbase, int size, sf::Color color, bool sel, int limit)
{
    this->limit = limit;
    this->isSelected = sel;
    this->textbase = textbase;
    this->text.clear();

    this->textbox.setCharacterSize(size);
    this->textbox.setFillColor(color);
    this->textbox.setFont(*font);
    this->textbox.setPosition(sf::Vector2f(x, y));

    if (sel) {
        this->textbox.setString(this->textbase + "_");
    } else {
        this->textbox.setString(this->textbase);
    }
}

Textbox::~Textbox() { }

void Textbox::setSelected(bool sel)
{
    this->isSelected = sel;
    if (!sel)
        textbox.setString(this->textbase + text.str());
    else
        textbox.setString(this->textbase + this->text.str() + "_");
}

std::string Textbox::getText()
{
    return this->text.str();
}

void Textbox::drawTo(sf::RenderTarget& window)
{
    window.draw(this->textbox);
}

void Textbox::typedOn(sf::Event ev)
{
    if (this->isSelected) {
        int charTyped = ev.text.unicode;
        if (charTyped < 128) {
            if (this->text.str().length() <= limit) {
                this->inputLogic(charTyped);
            } else if (charTyped == DELETE_KEY) {
                this->deleteLastChar();
            }
        }
    }
}

void Textbox::inputLogic(int charTyped)
{
    if (charTyped != DELETE_KEY && charTyped != ESCAPE_KEY && charTyped != ENTER_KEY) {
        text << static_cast<char>(charTyped);
    } else if (charTyped == DELETE_KEY) {
        if (text.str().length() > 0) {
            this->deleteLastChar();
        }
    }
    textbox.setString(this->textbase + this->text.str() + "_");
}

void Textbox::deleteLastChar()
{
    std::string t = this->text.str();
    std::string newT = "";
    for (int i = 0; i < t.length() - 1; i++) {
        newT += t[i];
    }
    this->text.str("");
    this->text << newT;

    textbox.setString(this->textbase + this->text.str());
}

void Textbox::refresh()
{
    this->text.str("");
    this->textbox.setString(this->textbase);
}

bool Textbox::isPressed(sf::Vector2f mousePos)
{
    if (this->textbox.getGlobalBounds().contains(mousePos)) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}