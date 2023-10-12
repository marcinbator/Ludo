#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "TeamName.h"
#include "Tile.h"

using namespace sf;
using namespace std;

class Pawn
{
	int id;
	Sprite sprite;
	Texture texture;
	Tile* currentTile;
	RenderWindow* window;
	bool isAtBase;
	bool isAtTarget;
public:
	Pawn() = delete;
	Pawn(int id, TeamName teamName, RenderWindow* window);
	void move(int tiles);
	void deploy();
	void setInBase();
	Tile* getCurrentTile();
	bool draw(Tile* tile);
};

