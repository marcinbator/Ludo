#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;
class Team;
class TossButton;

class Menu
{
    bool isDisplayed;
    int playersAmount;
    int aiPlayersAmount;

    Font font;
    Texture buttonTextures[4];

    Text title;
    Text text1;
    Text text2;
    Sprite playersButtons[4];
    Sprite aiPlayersButtons[4];
    TossButton* button;

    void setButtonPositions(int centerX, int centerY);
    void initMenu(int centerX, int centerY);

public:
    Menu(int centerX, int centerY);

    void draw(RenderWindow* window);
    void handleClick(Event event);
    void showWinners(Team** teams, int playersAmount);

    bool getIsDisplayed();
    int getPlayersAmount();
    int getAiPlayersAmount();
};