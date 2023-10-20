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

	bool isAtBase;
	bool isAtTarget;

	void initSprite();
	bool move(Tile* tile, RenderWindow* window, Board* board);
	bool deploy(int& dice, bool& canToss, RenderWindow* window, Board* board);
	int getNextTileId(int currentId);
	void checkIsAtTarget();

public:

	Pawn() = delete;
	Pawn(int id, Team* team, Tile* currentTile);

	void draw(Tile* tile, RenderWindow* window);
	bool handleClick(int& dice, bool& canToss, RenderWindow* window, Board* board);
	void setAtBase(RenderWindow* window, Board* board);
	void setIsAtBase(bool isAtBase);

	int getId();
	Team* getTeam();
	Tile* getCurrentTile();
	bool getIsAtBase();
	bool getIsAtTarget();
	bool isClicked(Event event);
	bool canMoveFurther(int tiles, Board* board);
};

