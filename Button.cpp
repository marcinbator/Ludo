#include "Button.h"

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
    this->text = Text(text, this->font, 20);
    this->text.setFillColor(sf::Color::Black);
    this->text.setOrigin(this->text.getGlobalBounds().width / 2, this->text.getGlobalBounds().height / 2);
    this->text.setPosition(x, y-5);
}

Button::Button(string text, string texturePath, int x, int y)
{
    this->font.loadFromFile("fonts/YoungSerif-Regular.ttf");
    this->initSprite(texturePath, x, y);
    this->initText(text, x, y);
}

void Button::draw(RenderWindow* window)
{
    window->draw(this->sprite);
    window->draw(this->text);
}

void Button::handleClick()
{
    cout << "Button clicked.\n";
}

void Button::setTexture(string texturePath)
{
    this->texture.loadFromFile(texturePath);
    this->sprite.setTexture(texture);
    this->text.setOrigin(this->text.getGlobalBounds().width / 2, this->text.getGlobalBounds().height / 2);
}

const Sprite Button::getSprite()
{
    return this->sprite;
}

const bool Button::isClicked(Event event)
{
    if (this->sprite
        .getGlobalBounds()
        .contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
    {
        return true;
    }
    return false;
}
