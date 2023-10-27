#include "TossButton.h"

TossButton::TossButton(string text,  int x, int y) 
    : Button(text, "images/button1.png",  x, y)
{
    this->canToss = true;
    initText(text);
    cout << "Toss button initialized successfully.\n";
}

void TossButton::handleClick(int& dice, Board* board)
{
    dice = random(1, 6);
    board->setDiceTexture("images/" + to_string(dice) + "dice.png");
    cout << "Toss button clicked. Value: " << dice << endl;
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