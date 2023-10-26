#pragma once
#include <iostream>
#include "Random.h"
#include <SFML/Graphics.hpp>

using namespace std;

class Board;
class Team;
class Pawn;
class TossButton;
class Dial;
class Ai;
class InitialMenu;
class LeaderBoard;

class Game
{
    int dice{};
    int playersAmount{};
    int aiPlayersAmount{};
    int playersTotalAmount{};
    int currentTeamId{};
    int currentFreePodiumPlace = 1;
    int delayTime = 1000;
    bool isWarp = false;
    bool& restart;
    Board* board;
    Team* teams[4];
    Pawn* pawns[16];
    Dial* dial;
    TossButton* tossButton;
    InitialMenu* initialMenu;
    LeaderBoard* leaderBoard;
    Ai* ai;
    sf::RenderWindow* window;
    sf::Clock delayClock;
public:
    Game(bool& restart);
    ~Game();
    void update();
    void render();
    void createTeams();
    bool isRunning() const;
private:
    void initWindow();
    void initControls();
    void renderPawns();

    void pollEvents();

    void handleAiMove();
    void handleTossClick();
    void handlePawnClick(int pawnId);
    void handleAllObstructed();
    void handleSingleWin();
    void handleGameEnd();

    void setNextTeamId();
};
