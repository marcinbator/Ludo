#include "Dial.h"

Dial::Dial(string text, int x, int y)
{
    initText(text, x, y);
    cout << "Dial window initialized successfully.\n";
}

void Dial::draw(RenderWindow* window)
{
    this->text.setOrigin(this->text.getGlobalBounds().width / 2, this->text.getGlobalBounds().height / 2);
    window->draw(this->text);
}

void Dial::setText(string text)
{
    this->text.setFillColor(Color::White);
    this->text.setString(text);
}

void Dial::setText(string text, Color color)
{
    this->text.setFillColor(color);
    this->text.setString(text);
}

//private

void Dial::initText(string text, int x, int y)
{
    this->font.loadFromFile("fonts/YoungSerif-Regular.ttf");
    this->text.setFont(this->font);
    this->text.setCharacterSize(20);
    this->text.setFillColor(Color::White);
    this->text.setString(text);
    this->text.setOrigin(this->text.getGlobalBounds().width / 2, this->text.getGlobalBounds().height / 2);
    this->text.setPosition(x, y);
}