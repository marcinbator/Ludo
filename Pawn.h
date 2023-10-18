#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;
class Tile;
class Team;
class Board;

class Pawn
{
	int id;
	Team* team;
	Tile* currentTile;
	Texture texture;
	Sprite sprite;
	RenderWindow* window;
	Board* board;

	bool isAtBase;
	bool isAtTarget;

	int getNextTileId(int currentId);
	void checkIsAtTarget();
	void initSprite();
	bool deploy(int& dice, bool& canToss, Board* board);

public:

	Pawn() = delete;
	Pawn(int id, Team* team, RenderWindow* window, Tile* currentTile, Board* board);

	void draw(Tile* tile);
	bool move(Tile* tile, Board* board);
	void setAtBase(Board* board);
	void setIsAtBase(bool isAtBase);
	bool handleClick(int& dice, bool& canToss, Board* board);

	int getId();
	Team* getTeam();
	Tile* getCurrentTile();
	bool isClicked(Event event);
	bool getIsAtBase();
	bool getIsAtTarget();
	bool canMoveFurther(int tiles, Board* board);
};

