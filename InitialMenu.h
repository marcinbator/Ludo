#pragma once
#include "Menu.h"

using namespace sf;
using namespace std;
class Team;
class TossButton;
class MenuConfirmButton;
class Dial;
class Game;

class InitialMenu : public Menu
{
    int playersAmount;
    int aiPlayersAmount;
    int level;

    Text text1;
    Text text2;
    Text text3;
    ColorSelectButton* playersButtons[4];
    ColorSelectButton* aiPlayersButtons[4];
    string playersColors[4];
    string aiPlayersColors[4];
    Button* levelButtons[3];
    MenuConfirmButton* button;

    void initMenu(int centerX, int centerY);
    void handleLevelClick(int index);
    void handlePlayerButtonClick(int index);
    void handleAiPlayerButtonClick(int index);

public:
    InitialMenu(int centerX, int centerY);
    ~InitialMenu();

    void draw(RenderWindow* window, int centerX, int centerY);
    void handleClick(Event event, Game* game);
    void showWinners(Team** teams, int playersAmount);

    int getLevel();
    int getPlayersAmount();
    int getAiPlayersAmount();
    string* getPlayersColors();
    string* getAiPlayersColors();
};