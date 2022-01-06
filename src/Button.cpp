#include "../include/Button.h"

Button::Button(float x, float y, float width, float height,
    sf::Font *font, std::string text, int fontSize,
    sf::Color idleColor, sf::Color hoverColor)
{
    this->buttonState = BTN_IDLE;

    this->shape.setPosition(sf::Vector2f(x, y));
    this->shape.setSize(sf::Vector2f(width, height));
    
    this->text.setString(text);
    this->text.setFont(*font);
    this->text.setFillColor(sf::Color::White);
    this->text.setCharacterSize(fontSize);
    auto textRect = this->text.getGlobalBounds();
    this->text.setOrigin(textRect.left + textRect.width/2.f,
                        textRect.top + textRect.height/2.f);
    this->text.setPosition(
        this->shape.getPosition().x + this->shape.getGlobalBounds().width / 2.f,
        this->shape.getPosition().y + this->shape.getGlobalBounds().height / 2.f
        );

    this->idleColor = idleColor;
    this->hoverColor = hoverColor;

    this->shape.setOutlineColor(sf::Color::White);
    this->shape.setOutlineThickness(3);
    this->shape.setFillColor(this->idleColor);
}

Button::~Button() {}

void Button::update(sf::Vector2f mousePos) {
    this->buttonState = BTN_IDLE;
    //Hover
    if (this->shape.getGlobalBounds().contains(mousePos)) {
        this->buttonState = BTN_HOVER;
    }

    switch (this->buttonState)
    {
    case BTN_IDLE:
        this->shape.setFillColor(this->idleColor);
        break;

    case BTN_HOVER:
        this->shape.setFillColor(this->hoverColor);
        this->shape.setOutlineThickness(3);
        break;

    default:
        break;
    }
}

void Button::drawTo(sf::RenderTarget& target) {
    target.draw(this->shape);
    target.draw(this->text);
}

//Accessors
const bool Button::isPressed() const {
    if (this->buttonState == BTN_HOVER) {
        return true;
    } else {
        return false;
    }
}

void Button::setColor(sf::Color color) {
    this->shape.setFillColor(color);
}