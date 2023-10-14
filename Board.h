#pragma once
#include "Tile.h"
class Board
{
	Tile* tiles[72];
	int centerX;
	int centerY;
	void initBoard();
	void setIds();
public:
	Board() = delete;
	Board(RenderWindow* window);
	Tile* getTileById(int id);
	Tile** getTiles();
	void drawBoard(RenderWindow* window);
};