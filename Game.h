#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Board.h"
#include "Team.h"
#include "Pawn.h"
#include "TossButton.h"
#include "Dial.h"
#include "Ai.h"

using namespace sf;
using namespace std;
class Menu;

class Game
{
    int dice;
    int currentFreePodiumPlace;
    int playersAmount;
    int aiPlayersAmount;
    int playersTotalAmount;
    int currentTeamId;
    RenderWindow* window;
    Board* board;
    Team* teams[4];
    Pawn* pawns[16];
    TossButton* tossButton;
    Dial* dial;
    Menu* menu;
    Ai ai;

    void initWindow();
    void initControls();
    void renderPawns();
    void handleTossClick();
    void handlePawnClick(int pawnId);
    void handleAllObstructed();
    void handleSingleWin();
    void handleGameEnd();
    void getNextTeamId();
    void pollEvents();
    void pollMenuEvents();

public:
    Game();
    ~Game();

    void update();
    void render();
    void createTeams();

    bool isRunning();
};
