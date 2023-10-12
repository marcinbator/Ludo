#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Board.h"

using namespace sf;
using namespace std;

class Game
{
    RenderWindow* window;
    void pollEvents();
    Board* board = nullptr;
public:
    Game();
    void update();
    void render();
    bool isRunning();
};