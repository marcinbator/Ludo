#pragma once
#include "Tile.h"
class Board
{
	Tile tiles[200];
	int centerX;
	int centerY;
	void setIds();
	void drawBoard(RenderWindow* window);
public:
	Board() = delete;
	Board(RenderWindow* window);
	Tile* getTileById(int id);
	Tile* getTiles();
};