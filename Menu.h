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
protected:

    bool isDisplayed;
    Font font;
    Text title;
    Dial* dial;

    void initMenu(int centerX, int centerY);
    void drawLogo(RenderWindow* window, int centerX, int centerY);

public:
    Menu(int centerX, int centerY);
    ~Menu();

    void draw(RenderWindow* window, int centerX, int centerY);

    bool getIsDisplayed();
};