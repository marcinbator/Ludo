#include "MenuConfirmButton.h"
#include "Menu.h"
#include "Dial.h"

void MenuConfirmButton::initText(string text, int x, int y)
{
    this->text = Text(text, this->font, 15);
    this->text.setFillColor(sf::Color::Black);
    this->text.setOrigin(this->text.getGlobalBounds().width / 2, this->text.getGlobalBounds().height / 2);
    this->text.setPosition(x, y + 10);
}

MenuConfirmButton::MenuConfirmButton(string text, int x, int y) : Button(text, x, y)
{
    this->initText(text, x, y-13);
}

bool MenuConfirmButton::handleClick(Menu* menu, Dial* dial)
{
    if (menu->getPlayersAmount() + menu->getAiPlayersAmount() == 0) {
        dial->setText("Zbyt mala liczba graczy!", Color::Red);
        return false;
    }
    return true;
}