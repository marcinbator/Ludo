#include "InitialMenu.h"
#include "Button.h"
#include "MenuConfirmButton.h"
#include "ColorSelectButton.h"

InitialMenu::InitialMenu(int centerX, int centerY) : Menu(centerX, centerY)
{
    this->submitButton = new MenuConfirmButton("Zatwierdz", centerX, centerY + 370);
    string textsStrings[] = { "Wybierz graczy", "Wybierz graczy SI", "Wybierz poziom trudnosci SI" };
    for (int i = 0; i < 3; i++) {
        this->texts[i] = Text(textsStrings[i], this->font, 20);
        this->texts[i].setFillColor(sf::Color::White);
        this->texts[i].setOrigin(this->texts[i].getGlobalBounds().width / 2, this->texts[i].getGlobalBounds().height / 2);
        this->texts[i].setPosition(centerX, centerY + i * 100);
    }
    string textures[] = { "Red", "Blue", "Green", "Yellow" };
    for (int i = 0; i < Game::MAX_TEAMS; i++) {
        this->playersButtons[i] = new ColorSelectButton(i, textures[i], centerX - 180 + i * 120, centerY + 50);
        this->aiPlayersButtons[i] = new ColorSelectButton(i, textures[i], centerX - 180 + i * 120, centerY + 150);
        this->playersColors[i] = "";
        this->aiPlayersColors[i] = "";
    }
    string texts[] = { "Latwy", "Sredni", "Trudny" };
    for (int i = -1; i < 2; i++) {
        this->levelButtons[i + 1] = new Button(texts[i + 1], "images/button1.png", centerX + i * 150, centerY + 250);
    }
}

InitialMenu::~InitialMenu()
{
    delete this->submitButton;
    for (int i = 0; i < Game::MAX_TEAMS; i++) {
        delete this->playersButtons[i];
        delete this->aiPlayersButtons[i];
    }
}

void InitialMenu::draw(RenderWindow* window, int centerX, int centerY)
{
    this->dial->draw(window); //dial
    for (int i = 0; i < Game::MAX_TEAMS; i++) { //team buttons
        this->playersButtons[i]->draw(window);
        this->aiPlayersButtons[i]->draw(window);
    }
    for (int i = 0; i < 3; i++) { //level buttons
        if (i == this->level) { //current level
            Text text = this->levelButtons[i]->getText();
            text.setFillColor(Color::Red);
            this->levelButtons[i]->setText(text);
        }
        else { //normal level
            Text text = this->levelButtons[i]->getText();
            text.setFillColor(Color::Black);
            this->levelButtons[i]->setText(text);
        }
        this->levelButtons[i]->draw(window);
    }
    this->submitButton->draw(window); //submit button
    this->drawLogo(window, centerX, centerY); //logo
    window->draw(this->title); //title
    for (int i = 0; i < 3; i++) { //texts
        window->draw(this->texts[i]);
    }
}

void InitialMenu::showWinners(Team** teams, int livePlayersAmount)
{
    Team* leaderboard[Game::MAX_TEAMS];
    for (int i = 0; i < livePlayersAmount; i++) {
        if (teams[i]->getStanding() != 0) { //player not last
            leaderboard[teams[i]->getStanding() - 1] = teams[i];
        }
        else {
            leaderboard[livePlayersAmount - 1] = teams[i];
        }
    }
    system("cls");
    for (int i = 0; i < livePlayersAmount; i++) {
        cout << "\tMiejsce " + to_string(i + 1) << ": " << leaderboard[i]->getName() << endl;
    }
}

void InitialMenu::pollMenuEvents(RenderWindow* window, Game* game, bool& restart)
{
    Event event;
    while (window->pollEvent(event))
    {
        if (event.type == Event::Closed)
        {
            restart = false;
            window->close();
        }
        else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
        {
            if (this->submitButton->isClicked(event)) { //submit
                if (this->submitButton->handleClick(this, this->dial)) {
                    this->isDisplayed = false;
                    game->initGame();
                }
            }
            for (int i = 0; i < Game::MAX_TEAMS; i++) { //player button
                if (this->playersButtons[i]->isClicked(event)) {
                    this->handlePlayerButtonClick(i);
                }
                if (this->aiPlayersButtons[i]->isClicked(event)) {
                    this->handleAiPlayerButtonClick(i);
                }
            }
            for (int i = 0; i < 3; i++) { //level buttons
                if (this->levelButtons[i]->isClicked(event)) {
                    this->level = i;
                }
            }
        }
    }
}

int InitialMenu::getLevel() const
{
    return this->level;
}

int InitialMenu::getPlayersAmount() const
{
    return this->livePlayersAmount;
}

int InitialMenu::getAiPlayersAmount() const
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

void InitialMenu::handlePlayerButtonClick(int index)
{
    this->playersButtons[index]->handleClick(this, this->dial, this->aiPlayersButtons[index]);
    this->livePlayersAmount = 0;
    for (int i = 0; i < Game::MAX_TEAMS; i++) { //selection logic
        if (this->playersButtons[i]->getIsSelected()) {
            this->playersColors[i] = this->playersButtons[i]->getColor();
            this->livePlayersAmount++;
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
    for (int i = 0; i < Game::MAX_TEAMS; i++) { //selection logic
        if (this->aiPlayersButtons[i]->getIsSelected()) {
            this->aiPlayersColors[i] = this->aiPlayersButtons[i]->getColor();
            this->aiPlayersAmount++;
        }
        else {
            this->aiPlayersColors[i] = "";
        }
    }
}