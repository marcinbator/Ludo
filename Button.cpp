#include "Button.h"

Button::Button(string text, string texturePath, int x, int y)
{
    this->font.loadFromFile("fonts/YoungSerif-Regular.ttf");
    this->initSprite(texturePath, x, y);
    this->initText(text, x, y);
}

void Button::draw(sf::RenderWindow* window)
{
    window->draw(this->sprite);
    window->draw(this->text);
}

void Button::setText(sf::Text text)
{
    this->text = text;
    this->text.setOrigin(this->text.getGlobalBounds().width / 2, this->text.getGlobalBounds().height / 2);
}

void Button::setTexture(string texturePath)
{
    this->texture.loadFromFile(texturePath);
    this->sprite.setTexture(texture);
    this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);
}

const sf::Sprite Button::getSprite() const
{
    return this->sprite;
}

const sf::Text Button::getText() const
{
    return this->text;
}

const bool Button::isClicked(sf::Event event) const
{
    return this->sprite
        .getGlobalBounds()
        .contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
}

void Button::initSprite(string texturePath, int x, int y)
{
    this->texture.loadFromFile(texturePath);
    this->sprite.setTexture(this->texture);
    this->sprite.setPosition(x, y);
    this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);
    this->sprite.setScale(1.5, 1);
}

void Button::initText(string text, int x, int y)
{
    this->text = sf::Text(text, this->font, 20);
    this->text.setFillColor(sf::Color::Black);
    this->text.setOrigin(this->text.getGlobalBounds().width / 2, this->text.getGlobalBounds().height / 2);
    this->text.setPosition(x, y - 5);
}