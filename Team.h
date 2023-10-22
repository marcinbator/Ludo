#pragma once
#include <string>
#include "Pawn.h"
#include "Tile.h"

using namespace std;
class Board;

class Team
{
	int id;
	string name;
	bool isAi;
	int standing;
	string texturePath;
	Tile* startingTile;
	Pawn* pawns[4];

public:
	Team() = delete;
	Team(int id, bool isAi, string name, Tile* startingTile, string texturePath);

	void setPawns(Pawn* pawns[4]);
	void setStanding(int standing);

	int getId();
	string getName();
	bool getIsAi();
	Pawn** getPawns();
	int getStanding();
	Tile* getStartingTile();
	string getTexturePath();
	bool isWin();
	bool areAllObstructed(int dice, Board* board);
};