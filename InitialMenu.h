#pragma once
#include "Menu.h"
#include "Team.h"
#include "Game.h"
#include "Dial.h"

using namespace std;

class Button;
class MenuConfirmButton;
class ColorSelectButton;

class InitialMenu : public Menu
{
    int livePlayersAmount{};
    int aiPlayersAmount{};
    int level{};
    ColorSelectButton* playersButtons[Game::MAX_TEAMS];
    ColorSelectButton* aiPlayersButtons[Game::MAX_TEAMS];
    string playersColors[Game::MAX_TEAMS];
    string aiPlayersColors[Game::MAX_TEAMS];
    Button* levelButtons[3];
    MenuConfirmButton* submitButton;
    sf::Text texts[3];
public:
    InitialMenu() = delete;
    InitialMenu(int centerX, int centerY);
    ~InitialMenu();

    void draw(sf::RenderWindow* window, int centerX, int centerY);
    void pollMenuEvents(sf::RenderWindow* window, Game* game, bool& restart);

    int getLevel() const;
    int getPlayersAmount() const;
    int getAiPlayersAmount() const;
    string* getPlayersColors();
    string* getAiPlayersColors();
private:
    void handlePlayerButtonClick(int index);
    void handleAiPlayerButtonClick(int index);
};