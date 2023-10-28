#pragma once
#include <string>
#include "Pawn.h"
#include "Tile.h"
#include "Board.h"
#include "Game.h"

using namespace std;

class Ai;

class Team
{
	int id{};
	int possibleMoves{};
	string name;
	int prime{};
	int standing{};
	bool isAi;
	Ai* ai;
	string texturePath;
	Tile* startingTile;
	Pawn* pawns[Game::PAWNS_TEAM];

public:
	Team() = delete;
	Team(int id, bool isAi, string name, Tile* startingTile, string texturePath, int level);
	~Team();

	void setId(int id);
	void setPawns(Pawn* pawns[Game::PAWNS_TEAM]);
	void setStanding(int standing);
	void setPrime(int prime);

	int getId() const;
	int getPrime() const;
	int getIsPossibleMovesOne(int currentTeamId, int dice, sf::RenderWindow* window, Board* board) const;
	string getName() const;
	bool getIsAi() const;
	Ai* getAi();
	Pawn** getPawns();
	int getStanding() const;
	Tile* getStartingTile();
	string getTexturePath() const;
	bool isWin() const;
	bool areAllObstructed(int dice, Board* board) const;
};