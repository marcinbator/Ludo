#include "TossButton.h"
#include "Random.h"

TossButton::TossButton(string text,  int x, int y)
{
    this->canToss = true;
    initSprite(x, y);
    initText(text);
    cout << "Toss button initialized successfully.\n";
}

void TossButton::draw(RenderWindow* window) {
    window->draw(this->sprite);
    window->draw(this->text);
}

void TossButton::handleClick(int& dice)
{
    if (this->canToss) {
        dice = random(1, 6);
    }
    cout << "Toss button clicked. Value: " << dice << endl;
}

const bool TossButton::isClicked(Event event)
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

void TossButton::initSprite(int x, int y)
{
    this->texture.loadFromFile("images/button1.png");
    this->sprite.setTexture(this->texture);
    this->sprite.setPosition(x, y);
    this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);
    this->sprite.setScale(1.5, 1);
}

void TossButton::initText(string text)
{
    this->font.loadFromFile("fonts/YoungSerif-Regular.ttf");
    this->text.setFont(this->font);
    this->text.setCharacterSize(16);
    this->text.setFillColor(sf::Color::Black);
    this->text.setString(text);
    this->text.setOrigin(this->text.getGlobalBounds().width / 2, this->text.getGlobalBounds().height / 2);
    this->text.setPosition(this->sprite.getPosition().x, this->sprite.getPosition().y - 3);
}