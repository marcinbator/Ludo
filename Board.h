#pragma once
#include "Tile.h"

using namespace sf;
class Button;

class Board
{
	int centerX;
	int centerY;
	Button* warp;
	Tile* tiles[72];

	void setCenter(RenderWindow* window);
	void initTiles();
	void drawLogo(RenderWindow* window);
	void initBoard();
	void setIds();

public:
	const static int TILES_AMOUNT = 72;
	const static int BASE_FIRST_ID = 100;
	const static int BASE_SIZE = 4;
	const static int LAST_TILE = 40;
	const static int TARGET_FIRST_ID = 50;
	const static int TARGET_LAST_ID = 53;

	Board() = delete;
	Board(RenderWindow* window);
	~Board();

	void drawBoard(RenderWindow* window);

	Tile** getTiles();
	Tile* getTileById(int id);
	int getCenterX();
	int getCenterY();
	Button* getWarp();
};