#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Board.h"
#include "Player.h"
#include "Pawn.h"

using namespace sf;
using namespace std;

class Game
{
    RenderWindow* window;
    void pollEvents();
    void renderPawns();
    Board* board = nullptr;
    Pawn* pawns = nullptr;
    Player* players = nullptr;
public:
    Game();
    void update();
    void render();
    void create();
    bool isRunning();

    void testMove();
};