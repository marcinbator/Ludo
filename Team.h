#pragma once
#include <string>
#include "Pawn.h"
#include "Tile.h"
#include "Board.h"
#include "Game.h"

using namespace std;

class Team
{
	int id{};
	int standing{};
	bool isAi;
	string name;
	string texturePath;
	Tile* startingTile;
	Pawn* pawns[Game::PAWNS_TEAM];

public:
	Team() = delete;
	Team(int id, bool isAi, string name, Tile* startingTile, string texturePath);

	void setPawns(Pawn* pawns[Game::PAWNS_TEAM]);
	void setStanding(int standing);

	int getId() const;
	string getName() const;
	bool getIsAi() const;
	Pawn** getPawns();
	int getStanding() const;
	Tile* getStartingTile();
	string getTexturePath() const;
	bool isWin() const;
	bool areAllObstructed(int dice, Board* board) const;
};