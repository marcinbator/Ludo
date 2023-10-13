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
    Board* board;
    Pawn* pawns[16];
    Player* players;
    void pollEvents();
    void renderPawns();
public:
    Game();
    void update();
    void render();
    void createTeams();
    bool isRunning();
    
    //
    void testMove();
};