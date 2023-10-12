#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Board.h"
#include "Pawn.h"

using namespace sf;
using namespace std;

class Game
{
    RenderWindow* window;
    void pollEvents();
    void renderPawns();
    Board* board = nullptr;
public:
    Game();
    void update();
    void render();
    bool isRunning();
};