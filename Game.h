#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Board.h"
#include "Team.h"
#include "Pawn.h"
#include "Button.h"
#include "Dial.h"

using namespace sf;
using namespace std;

class Game
{
    RenderWindow* window;
    Board* board;
    Button* tossButton;
    Dial* dial;
    int dice;
    Pawn* pawns[16];
    Team* teams[4];
    void renderPawns();
    void createTeams();
    void handleTossClick();
    void pollEvents();

public:
    Game();
    ~Game();

    void update();
    void render();

    bool isRunning();
};
