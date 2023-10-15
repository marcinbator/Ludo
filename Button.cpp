#include "Button.h"

Button::Button(string text,  int x, int y)
{
    this->canToss = true;
    this->font.loadFromFile("fonts/YoungSerif-Regular.ttf");
    this->text.setFont(this->font);
    this->text.setCharacterSize(16);
    this->text.setFillColor(sf::Color::Black);
    this->text.setString(text);
    this->texture.loadFromFile("images/button1.png");
    this->sprite.setTexture(this->texture);
    this->sprite.setPosition(x, y);
    this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);
    this->sprite.setScale(1.5, 1);
    this->text.setOrigin(this->text.getGlobalBounds().width / 2, this->text.getGlobalBounds().height / 2);
    this->text.setPosition(this->sprite.getPosition().x, this->sprite.getPosition().y-3);
}

void Button::draw(RenderWindow* window) {
    window->draw(this->sprite);
    window->draw(this->text);
}

void Button::handleClick(int& dice)
{
    if (this->canToss) {
        dice = this->random(1, 6);
        this->canToss = false;
    }
    cout << "Button clicked" << dice << endl;
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

//private

int Button::random(int min, int max)
{
    static bool first = true;
    if (first)
    {
        srand(time(NULL));
        first = false;
    }
    return min + rand() % ((max + 1) - min);
}