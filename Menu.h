#pragma once
#include <SFML/Graphics.hpp>
#include "ColorSelectButton.h"
#include <iostream>

using namespace sf;
using namespace std;
class Team;
class TossButton;
class MenuConfirmButton;
class Dial;
class Game;

class Menu
{
    bool isDisplayed;
    int playersAmount;
    int aiPlayersAmount;

    Font font;
    Dial* dial;
    Text title;
    Text text1;
    Text text2;
    ColorSelectButton* playersButtons[4];
    ColorSelectButton* aiPlayersButtons[4];
    string playersColors[4];
    string aiPlayersColors[4];
    MenuConfirmButton* button;

    void initMenu(int centerX, int centerY);
    void drawLogo(RenderWindow* window, int centerX, int centerY);
    void handlePlayerButtonClick(int index);
    void handleAiPlayerButtonClick(int index);

public:
    Menu(int centerX, int centerY);

    void draw(RenderWindow* window, int centerX, int centerY);
    void handleClick(Event event, Game* game);
    void showWinners(Team** teams, int playersAmount);

    bool getIsDisplayed();
    int getPlayersAmount();
    int getAiPlayersAmount();
    string* getPlayersColors();
    string* getAiPlayersColors();
};