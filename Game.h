#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include <iostream>

using namespace sf;
using namespace std;

class Game
{
    Tile tiles[100];
    RenderWindow* window;
    void pollEvents();
public:
    Game();
    void update();
    void render();
    bool isRunning();
};
