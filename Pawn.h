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

	bool isAtBase;
	bool isAtTarget;

	void deploy();
	int getNextTileId(int currentId);
	bool canMoveFurther(int tiles);

public:
	Pawn() = delete;
	Pawn(int id, Team* team, RenderWindow* window, Tile* currentTile);

	void draw(Tile* tile);
	bool move(Tile* tile);
	bool handleClick(int& tiles, Board* board, bool& canToss);

	Team* getTeam();
	Tile* getCurrentTile();
	bool isClicked(Event event);
};

