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
	bool canMoveFurther(int tiles);

public:
	Pawn() = delete;
	Pawn(int id, Team* team, RenderWindow* window, Tile* currentTile, Board* board);

	void draw(Tile* tile);
	bool move(Tile* tile);
	void setAtBase();
	void handleClick(int& dice, bool& canToss);

	Team* getTeam();
	Tile* getCurrentTile();
	bool isClicked(Event event);
	bool getIsAtBase();
};

