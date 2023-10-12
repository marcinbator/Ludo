#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "TeamName.h"

using namespace sf;
using namespace std;

class Pawn
{
	int id;
	Sprite sprite;
	TeamName teamName;
	int currentTileId;
	bool isAtBase;
	bool isAtTarget;
	bool setPosition(int tileId);
public:
	Pawn() = delete;
	Pawn(int id, TeamName teamName);
	void move(int tiles);
	void deploy();
	void setInBase();
	int getId();
	int getCurrentTileId();
	int getNextTileId();
	TeamName getTeamName();
};

