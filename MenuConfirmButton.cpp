#include "MenuConfirmButton.h"
#include "InitialMenu.h"
#include "Dial.h"

void MenuConfirmButton::initText(string text, int x, int y)
{
    this->text = Text(text, this->font, 15);
    this->text.setFillColor(sf::Color::Black);
    this->text.setOrigin(this->text.getGlobalBounds().width / 2, this->text.getGlobalBounds().height / 2);
    this->text.setPosition(x, y + 10);
}

MenuConfirmButton::MenuConfirmButton(string text, int x, int y) : Button(text, "images/button1.png", x, y)
{
    this->initText(text, x, y-13);
}

bool MenuConfirmButton::handleClick(InitialMenu* initialMenu, Dial* dial)
{
    if (initialMenu->getPlayersAmount() + initialMenu->getAiPlayersAmount() < 1) { //debug - <2
        dial->setText("Zbyt mala liczba graczy!", Color::Red);
        return false;
    }
    return true;
}