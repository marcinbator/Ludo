#include "Dial.h"

Dial::Dial(string text, int x, int y)
{
    initText(text, x, y);
}

void Dial::draw(sf::RenderWindow* window)
{
    this->text.setOrigin(this->text.getGlobalBounds().width / 2, this->text.getGlobalBounds().height / 2);
    window->draw(this->text);
}

void Dial::setText(string text)
{
    this->text.setFillColor(sf::Color::White);
    this->text.setString(text);
}

void Dial::setText(string text, sf::Color color)
{
    this->text.setFillColor(color);
    this->text.setString(text);
}

void Dial::initText(string text, int x, int y)
{
    this->font.loadFromFile("fonts/YoungSerif-Regular.ttf");
    this->text.setFont(this->font);
    this->text.setCharacterSize(20);
    this->text.setFillColor(sf::Color::White);
    this->text.setString(text);
    this->text.setOrigin(this->text.getGlobalBounds().width / 2, this->text.getGlobalBounds().height / 2);
    this->text.setPosition(x, y);
}