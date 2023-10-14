#pragma once
#include <string>
#include "Pawn.h"
#include "Tile.h"

using namespace std;

class Team
{
	int id;
	string name;
	string texturePath;
	Tile* startingTile;
	Pawn* pawns;

public:
	Team() = delete;
	Team(int id, string name, Tile* startingTile, string texturePath);

	void setPawns(Pawn* pawns[4]);

	Pawn* getPawns();
	string getName();
	Tile* getStartingTile();
	string getTexturePath();
};