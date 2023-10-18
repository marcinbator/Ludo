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
	bool move(Tile* tile);

public:

	Pawn() = delete;
	Pawn(int id, Team* team, RenderWindow* window, Tile* currentTile, Board* board);

	void draw(Tile* tile);
	void setAtBase();
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

