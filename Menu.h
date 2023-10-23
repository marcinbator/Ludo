#pragma once
#include <SFML/Graphics.hpp>
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
    Texture buttonTextures[4];
    Dial* dial;
    Text title;
    Text text1;
    Text text2;
    Sprite playersButtons[4];
    Sprite aiPlayersButtons[4];
    MenuConfirmButton* button;

    void setButtonPositions(int centerX, int centerY);
    void initMenu(int centerX, int centerY);

public:
    Menu(int centerX, int centerY);

    void draw(RenderWindow* window);
    void handleClick(Event event, Game* game);
    void showWinners(Team** teams, int playersAmount);

    bool getIsDisplayed();
    int getPlayersAmount();
    int getAiPlayersAmount();
};