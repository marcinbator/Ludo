#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Team.h"
#include "Tile.h"

using namespace sf;
using namespace std;

class Pawn
{
	int id;
	Sprite sprite;
	Tile* currentTile;
	bool isAtBase;
	bool isAtTarget;
	Team* team;
	bool setPosition(Tile* tile);
public:
	Pawn() = delete;
	Pawn(int id, Team* team);
	void move(int tiles);
	void deploy();
	void setTeamId(int id);
	void setInBase();
	int getId();
	Tile* getCurrentTile();
	Tile* getNextTile();
};

