#include "Menu.h"
#include "Team.h"
#include "TossButton.h"
#include "MenuConfirmButton.h"
#include "Dial.h"
#include "Game.h"

Menu::Menu(int centerX, int centerY)
{
    this->isDisplayed = true;
    this->playersAmount = 1;
    this->aiPlayersAmount = 3;
    this->dial = new Dial("Witaj w grze!", centerX, centerY - 80);
    this->button = new MenuConfirmButton("Zatwierdz", centerX, centerY + 270);
    this->initMenu(centerX, centerY);

    string textures[] = {"tileRed.png", "tileBlue.png", "tileGreen.png", "tileYellow.png"};
    for (int i = 0; i < 4; i++) {
        buttonTextures[i].loadFromFile("images/" + textures[i]);
        this->playersButtons[i].setTexture(buttonTextures[i]);
        this->aiPlayersButtons[i].setTexture(buttonTextures[i]);
    }
    this->setButtonPositions(centerX, centerY);
}

void Menu::draw(RenderWindow* window)
{
    this->dial->draw(window);
    window->draw(this->title);
    window->draw(this->text1);
    window->draw(this->text2);

    for (int i = 0; i < 4; i++) {
        window->draw(this->playersButtons[i]);
        window->draw(this->aiPlayersButtons[i]);
    }

    this->button->draw(window);
}

void Menu::handleClick(Event event, Game* game)
{
    if (this->button->isClicked(event)) {
        if (this->button->handleClick(this, this->dial)) {
            game->createTeams();
            this->isDisplayed = false;
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

void Menu::setButtonPositions(int centerX, int centerY)
{

    for (int i = 0; i < 4; i++) {
        this->playersButtons[i].setOrigin(this->playersButtons[i].getGlobalBounds().width / 2, this->playersButtons[i].getGlobalBounds().height / 2);
        this->playersButtons[i].setPosition(centerX - 180 + i * 120, centerY + 50);
        this->aiPlayersButtons[i].setOrigin(this->aiPlayersButtons[i].getGlobalBounds().width / 2, this->aiPlayersButtons[i].getGlobalBounds().height / 2);
        this->aiPlayersButtons[i].setPosition(centerX - 180 + i * 120, centerY + 150);
    }
}
