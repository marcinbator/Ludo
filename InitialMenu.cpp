#include "InitialMenu.h"
#include "Button.h"
#include "MenuConfirmButton.h"
#include "ColorSelectButton.h"

InitialMenu::InitialMenu(int centerX, int centerY) : Menu(centerX, centerY)
{
    this->initBackground(centerX, centerY);
    this->submitButton = new MenuConfirmButton("Zatwierdz", centerX, centerY + 370);
    string textsStrings[] = { "Wybierz graczy", "Wybierz graczy SI", "Wybierz poziom trudnosci SI" };
    for (int i = 0; i < 3; i++) {
        this->texts[i] = sf::Text(textsStrings[i], this->font, 20);
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
        this->levelButtons[i + 1] = new Button(texts[i + 1], string(TEXTURE_PATH) + "button1.png", centerX + i * 150, centerY + 250);
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

void InitialMenu::draw(sf::RenderWindow* window, int centerX, int centerY)
{
    window->draw(this->background);
    this->dial->draw(window); //dial
    for (int i = 0; i < Game::MAX_TEAMS; i++) { //team buttons
        this->playersButtons[i]->draw(window);
        this->aiPlayersButtons[i]->draw(window);
    }
    for (int i = 0; i < 3; i++) { //level buttons
        if (i == this->level) { //current level
            sf::Text text = this->levelButtons[i]->getText();
            text.setFillColor(sf::Color::Red);
            this->levelButtons[i]->setText(text);
        }
        else { //normal level
            sf::Text text = this->levelButtons[i]->getText();
            text.setFillColor(sf::Color::Black);
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

void InitialMenu::pollMenuEvents(sf::RenderWindow* window, Game* game, bool& restart)
{
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            restart = false;
            window->close();
        }
        else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
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