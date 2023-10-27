#include "MenuConfirmButton.h"

void MenuConfirmButton::initText(string text, int x, int y)
{
    this->text = sf::Text(text, this->font, 15);
    this->text.setFillColor(sf::Color::Black);
    this->text.setOrigin(this->text.getGlobalBounds().width / 2, this->text.getGlobalBounds().height / 2);
    this->text.setPosition(x, y + 10);
}

MenuConfirmButton::MenuConfirmButton(string text, int x, int y) : Button(text, string(TEXTURE_PATH) + "button1.png", x, y)
{
    this->initText(text, x, y-13);
    this->sprite.scale(1.5, 1.5);
}

bool MenuConfirmButton::handleClick(InitialMenu* initialMenu, Dial* dial)
{
    if (initialMenu->getPlayersAmount() + initialMenu->getAiPlayersAmount() < Game::MIN_PLAYERS) {
        dial->setText("Zbyt mala liczba graczy!", sf::Color::Red);
        return false;
    }
    return true;
}