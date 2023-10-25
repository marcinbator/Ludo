#include "InitialMenu.h"
#include "Team.h"
#include "MenuConfirmButton.h"
#include "Game.h"

void InitialMenu::handlePlayerButtonClick(int index)
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

void InitialMenu::handleAiPlayerButtonClick(int index)
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

InitialMenu::InitialMenu(int centerX, int centerY) : Menu(centerX, centerY)
{
    this->playersAmount = 0;
    this->aiPlayersAmount = 0;
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

InitialMenu::~InitialMenu()
{
    delete this->button;
    for (int i = 0; i < 4; i++) {
        delete this->playersButtons[i];
        delete this->aiPlayersButtons[i];
    }
}

void InitialMenu::handleClick(Event event, Game* game)
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

void InitialMenu::showWinners(Team** teams, int playersAmount)
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

void InitialMenu::draw(RenderWindow* window, int centerX, int centerY)
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

int InitialMenu::getPlayersAmount()
{
    return this->playersAmount;
}

int InitialMenu::getAiPlayersAmount()
{
    return this->aiPlayersAmount;
}

string* InitialMenu::getPlayersColors()
{
    return this->playersColors;
}

string* InitialMenu::getAiPlayersColors()
{
    return this->aiPlayersColors;
}

//private

void InitialMenu::initMenu(int centerX, int centerY)
{
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