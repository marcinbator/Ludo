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
	string texturePath;
	Tile* startingTile;
	Pawn* pawns[4];

public:
	Team() = delete;
	Team(int id, string name, Tile* startingTile, string texturePath);
	~Team();

	void setPawns(Pawn* pawns[4]);

	Pawn** getPawns();
	string getName();
	int getId();
	Tile* getStartingTile();
	string getTexturePath();
	bool areAllObstructed(int dice, Board* board);
	bool isWin();
};