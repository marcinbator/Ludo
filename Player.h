#pragma once
#include <string>
#include "Pawn.h"
#include "Tile.h"

using namespace std;


class Player
{
	int id;
	string name;
	Pawn* pawns;
	Tile* startingTile;
public:
	Player() = delete;
	Player(int id, string name, Pawn* pawns, Tile* startingTile);
	Pawn* getPawns();
	string getName();
	Tile* getStartingTile();
};

