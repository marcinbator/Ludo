#pragma once
#include "Tile.h"
class Board
{
	Tile tiles[100];
	int centerX;
	int centerY;
public:
	Board() = delete;
	Board(RenderWindow* window);
	void drawBoard(RenderWindow* window);
	Tile* getTiles();
	void setIds();
};