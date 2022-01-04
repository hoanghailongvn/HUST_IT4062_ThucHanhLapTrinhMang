#include "../include/CharacterBox.h"

using namespace std;

CharacterBox::CharacterBox(float x, float y, float size, sf::Font *font, char character) {
    this->font = font;

    this->shape.setPosition(sf::Vector2f(x, y));
    this->shape.setSize(sf::Vector2f(size, size));
    this->shape.setOutlineColor(sf::Color::White);
    this->shape.setOutlineThickness(2);
    this->shape.setFillColor(sf::Color::Black);

    this->character.setString(character);
    this->character.setFont(*this->font);
    this->character.setCharacterSize(50);
    auto textRect = this->character.getGlobalBounds();
    this->character.setOrigin(textRect.left + textRect.width/2.f,
                        textRect.top + textRect.height/2.f);
    this->character.setPosition(
        this->shape.getPosition().x + this->shape.getGlobalBounds().width / 2.f,
        this->shape.getPosition().y + this->shape.getGlobalBounds().height / 2.f
        );
}

CharacterBox::~CharacterBox() {}

void CharacterBox::drawTo(sf::RenderTarget& target) {
    target.draw(this->shape);
    target.draw(this->character);
}