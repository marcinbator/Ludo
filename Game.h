#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include <iostream>

using namespace sf;
using namespace std;

class Game
{
    int centerX;
    int centerY;
    void drawBoard();
    RenderWindow& window;
    Tile tiles[18];
public:
    Game(RenderWindow& window);
    void run();
};
