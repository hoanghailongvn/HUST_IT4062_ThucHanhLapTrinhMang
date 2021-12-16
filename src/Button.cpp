#include "../include/Button.h"

Button::Button(float x, float y, float width, float height,
    sf::Font *font, std::string text, int fontSize,
    sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
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
    this->activeColor = activeColor;

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

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            this->buttonState = BTN_ACTIVE;
        }
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

    case BTN_ACTIVE:
        this->shape.setFillColor(this->activeColor);
        break;

    default:
        this->shape.setFillColor(sf::Color::Red);
        break;
    }
}

void Button::drawTo(sf::RenderTarget& target) {
    target.draw(this->shape);
    target.draw(this->text);
}

//Accessors
const bool Button::isPressed() const {
    if (this->buttonState == BTN_ACTIVE) {
        return true;
    } else {
        return false;
    }
}