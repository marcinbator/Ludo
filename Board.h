#pragma once
#include "Tile.h"
class Board
{
	int centerX;
	int centerY;
	Tile* tiles[72];
	void initBoard();
	void setIds();

public:
	Board() = delete;
	Board(RenderWindow* window);
	~Board();

	void drawBoard(RenderWindow* window);

	Tile** getTiles();
	Tile* getTileById(int id);
};