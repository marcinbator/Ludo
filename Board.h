#pragma once
#include "Tile.h"
class Board
{
	Tile* tiles;
	int centerX;
	int centerY;
public:
	Board(Tile* tiles, RenderWindow* window);
	void drawBoard(RenderWindow* window);
	void setIds();
};

