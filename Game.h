#pragma once
#pragma warning(disable:6385)
#include <iostream>
#include "Random.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

constexpr auto TEXTURE_PATH = "images/";

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
    static const int MOVE_SOUND_ID = 0;
    static const int STRIKE_SOUND_ID = 1;
    static const int OBSTRUCTED_SOUND_ID = 2;
    static const int WIN_SOUND_ID = 3;

    int dice{};
    int livePlayersAmount{};
    int aiPlayersAmount{};
    int playersAmount{};
    int currentTeamId{};
    int currentFreePodiumPlace = 1;
    int delayTime = 1000;
    bool isWarp = false;
    bool isSound = true;
    bool& restart;
    Board* board;
    Team* teams[4];
    Pawn* pawns[16];
    InitialMenu* initialMenu;
    LeaderBoard* leaderBoard;
    sf::RenderWindow* window;
    sf::Clock delayClock;
    sf::SoundBuffer musicBuffer;
    sf::Sound music;
    sf::SoundBuffer soundsBuffers[4];
    sf::Sound sounds[4];
public:
    static const int PAWNS_TEAM = 4;
    static const int MAX_TEAMS = 4;
    static const int MIN_PLAYERS = 1; //debug = normal->2

    Game() = delete;
    Game(bool& restart);
    ~Game();
    void update();
    void render();
    void initGame();
    bool inline isRunning() const { return this->window->isOpen(); };
private:
    void initWindow();
    void initSounds();
    void createLivePlayers(const string* names, const int *baseTiles, const int* startTiles);
    void createAiPlayers(const string* names, const int* baseTiles, const int* startTiles);
    void orderPlayers(const string* namesOrder);
    void renderPawns();
    
    void handleAiMove();
    void handlePlayerTossClick();
    void handlePawnClick(int pawnId);
    void handleMouseOverPawn(int pawnId);
    void handleWarpClick();
    void handleSoundClick();
    void handleAllObstructed();
    void handleSingleWin();
    void handleGameEnd();

    void delay(int time, string dial);
    void setNextTeamId(int diceT);
    void selectPlayer();
    void pollEvents();
};