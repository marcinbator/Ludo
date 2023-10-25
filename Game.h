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
class InitialMenu;
class LeaderBoard;

class Game
{

    int dice;
    bool isWarp;
    bool& restart;
    int currentFreePodiumPlace;
    int playersAmount;
    int aiPlayersAmount;
    int playersTotalAmount;
    int currentTeamId;
    int delayTime;
    RenderWindow* window;
    Board* board;
    Team* teams[4];
    Pawn* pawns[16];
    TossButton* tossButton;
    Dial* dial;
    InitialMenu* menu;
    LeaderBoard* leaderBoard;
    Ai* ai;
    Clock delayClock;

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
    void pollLeaderboardEvents();

public:
    Game(bool& restart);
    ~Game();

    void update();
    void render();
    void createTeams();

    bool isRunning();
};
