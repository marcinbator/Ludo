#include "Menu.h"
#include "Team.h"
#include "TossButton.h"
#include "MenuConfirmButton.h"
#include "Dial.h"
#include "Game.h"

void Menu::handlePlayerButtonClick(int index)
{
    this->playersButtons[index]->handleClick(this, this->dial, this->aiPlayersButtons[index]);
    this->playersAmount = 0;
    for (int i = 0; i < 4; i++) {
        if (this->playersButtons[i]->getIsSelected()) {
            this->playersColors[i] = this->playersButtons[i]->getColor();
            this->playersAmount++;
        }
        else {
            this->playersColors[i] = "";
        }
    }
}

void Menu::handleAiPlayerButtonClick(int index)
{
    this->aiPlayersButtons[index]->handleClick(this, this->dial, this->playersButtons[index]);
    this->aiPlayersAmount = 0;
    for (int i = 0; i < 4; i++) {
        if (this->aiPlayersButtons[i]->getIsSelected()) {
            this->aiPlayersColors[i] = this->aiPlayersButtons[i]->getColor();
            this->aiPlayersAmount++;
        }
        else {
            this->aiPlayersColors[i] = "";
        }
    }
}

Menu::Menu(int centerX, int centerY)
{
    this->isDisplayed = true;
    this->playersAmount = 0;
    this->aiPlayersAmount = 0;
    this->dial = new Dial("Witaj w grze!", centerX, centerY - 80);
    this->button = new MenuConfirmButton("Zatwierdz", centerX, centerY + 270);
    this->initMenu(centerX, centerY);
    string textures[] = {"Red", "Blue", "Green", "Yellow"};
    for (int i = 0; i < 4; i++) {
        this->playersButtons[i] = new ColorSelectButton(i, textures[i], centerX - 180 + i * 120, centerY + 50);
        this->aiPlayersButtons[i] = new ColorSelectButton(i, textures[i], centerX - 180 + i * 120, centerY + 150);
        this->playersColors[i] = "";
        this->aiPlayersColors[i] = "";
    }
}

void Menu::draw(RenderWindow* window, int centerX, int centerY)
{
    this->dial->draw(window);
    window->draw(this->title);
    window->draw(this->text1);
    window->draw(this->text2);
    for (int i = 0; i < 4; i++) {
        this->playersButtons[i]->draw(window);
        this->aiPlayersButtons[i]->draw(window);
    }
    this->button->draw(window);
    this->drawLogo(window, centerX, centerY);
}

void Menu::handleClick(Event event, Game* game)
{
    if (this->button->isClicked(event)) {
        if (this->button->handleClick(this, this->dial)) {
            game->createTeams();
            this->isDisplayed = false;
        }
    }
    for (int i = 0; i < 4; i++) {
        if (this->playersButtons[i]->isClicked(event)) {
            this->handlePlayerButtonClick(i);
        }
        if (this->aiPlayersButtons[i]->isClicked(event)) {
            this->handleAiPlayerButtonClick(i);
        }
    }
}

void Menu::showWinners(Team** teams, int playersAmount)
{
    system("cls");
    Team* leaderboard[4];
    for (int i = 0; i < playersAmount; i++) {
        if (teams[i]->getStanding() != 0) {
            leaderboard[teams[i]->getStanding() - 1] = teams[i];
        }
        else {
            leaderboard[playersAmount - 1] = teams[i];
        }
    }
    for (int i = 0; i < playersAmount; i++) {
        cout << "\tMiejsce " + to_string(i + 1) << ": " << leaderboard[i]->getName() << endl;
    }
}

bool Menu::getIsDisplayed()
{
    return this->isDisplayed;
}

int Menu::getPlayersAmount()
{
    return this->playersAmount;
}

int Menu::getAiPlayersAmount()
{
    return this->aiPlayersAmount;
}

string* Menu::getPlayersColors()
{
    return this->playersColors;
}

string* Menu::getAiPlayersColors()
{
    return this->aiPlayersColors;
}

//private

void Menu::initMenu(int centerX, int centerY)
{
    this->font.loadFromFile("fonts/YoungSerif-Regular.ttf");

    //title
    this->title = Text("Menu", this->font, 30);
    this->title.setFillColor(sf::Color::White);
    this->title.setOrigin(this->title.getGlobalBounds().width / 2, this->title.getGlobalBounds().height / 2);
    this->title.setPosition(centerX, centerY - 130);

    //text1
    this->text1 = Text("Wybierz graczy", this->font, 20);
    this->text1.setFillColor(sf::Color::White);
    this->text1.setOrigin(this->text1.getGlobalBounds().width / 2, this->text1.getGlobalBounds().height / 2);
    this->text1.setPosition(centerX, centerY);

    //text2
    this->text2 = Text("Wybierz graczy SI", this->font, 20);
    this->text2.setFillColor(sf::Color::White);
    this->text2.setOrigin(this->text2.getGlobalBounds().width / 2, this->text2.getGlobalBounds().height / 2);
    this->text2.setPosition(centerX, centerY + 100);
}

void Menu::drawLogo(RenderWindow* window, int centerX, int centerY)
{
    Texture texture;
    texture.loadFromFile("images/logo.png");
    Sprite sprite(texture);
    sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
    sprite.setPosition(centerX, centerY - 40 * 9);
    sprite.setScale(0.3, 0.3);
    window->draw(sprite);
}