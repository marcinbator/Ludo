#include "Button.h"

Button::Button(string text, string texturePath, int x, int y)
{
    this->font.loadFromFile(string(FONTS_PATH)+"YoungSerif-Regular.ttf");
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

sf::Sprite Button::getSprite() const
{
    return this->sprite;
}

sf::Text Button::getText() const
{
    return this->text;
}

void Button::initSprite(string texturePath, int x, int y)
{
    this->texture.loadFromFile(texturePath);
    this->sprite.setTexture(this->texture);
    this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);
    this->sprite.setPosition(x, y);
}

void Button::initText(string text, int x, int y)
{
    this->text = sf::Text(text, this->font, 16);
    this->text.setFillColor(sf::Color::Black);
    this->text.setOrigin(this->text.getGlobalBounds().width / 2, this->text.getGlobalBounds().height / 2);
    this->text.setPosition(x, y - 5);
}