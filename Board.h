#pragma once
#include "Tile.h"
class Board
{
	int centerX;
	int centerY;
	Tile* tiles[72];
	void initBoard();
	void setIds();
	void drawLogo(sf::RenderWindow* window);

public:
	const static int BOARD_SIZE = 72;
	const static int BASE_FIRST_ID = 100;
	const static int BASE_SIZE = 4;
	const static int LAST_TILE = 40;
	const static int BASE_DISTANCE = 50;
	const static int BASE_DISTANCE_END = 53;

	Board() = delete;
	Board(RenderWindow* window);
	void setCenter(sf::RenderWindow* window);
	void initTiles();
	~Board();

	void drawBoard(RenderWindow* window);

	Tile** getTiles();
	Tile* getTileById(int id);
	int getCenterX();
	int getCenterY();
};