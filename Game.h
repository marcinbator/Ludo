#pragma once
#pragma warning(disable:6385)
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
    int livePlayersAmount{};
    int aiPlayersAmount{};
    int playersAmount{};
    int currentTeamId{};
    int currentFreePodiumPlace = 1;
    int delayTime = 1000;
    bool isWarp = false;
    bool& restart;
    Board* board;
    Team* teams[4];
    Pawn* pawns[16];
    InitialMenu* initialMenu;
    LeaderBoard* leaderBoard;
    Ai* ai;
    sf::RenderWindow* window;
    sf::Clock delayClock;
public:
    const int PAWNS_TEAM = 4;
    Game() = delete;
    Game(bool& restart);
    ~Game();
    void update();
    void render();
    void initGame();
    bool inline isRunning() const { return this->window->isOpen(); };
private:
    void initWindow();
    void createLivePlayers(const string* names, const int *baseTiles, const int* startTiles);
    void createAiPlayers(const string* names, const int* baseTiles, const int* startTiles);
    void renderPawns();
    
    void handleAiMove();
    void handlePlayerTossClick();
    void handlePawnClick(int pawnId);
    void handleWarpClick();
    void handleAllObstructed();
    void handleSingleWin();
    void handleGameEnd();

    void delay(int time, string dial);
    void setNextTeamId();
    void pollEvents();
};