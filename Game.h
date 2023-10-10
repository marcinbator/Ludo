#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"

using namespace sf;

class Game
{
public:
    Game(RenderWindow& window);
    void run();

private:
    RenderWindow& window;
    Tile tiles[18];
    int centerX;
    int centerY;
    void drawBoard();
};
