#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Tile;
class Team;

class Pawn
{
	int id;
	Sprite sprite;
	Texture texture;
	Team* team;
	Tile* currentTile;
	RenderWindow* window;
	bool isAtBase;
	bool isAtTarget;
	void draw(Tile* tile);
public:
	Pawn() = delete;
	Pawn(int id, Team* team, RenderWindow* window, Tile* currentTile);
	void move(int tiles);
	void deploy();
	void setTeam(Team* team);
	Team* getTeam();
	void setInBase();
	int getId();
	bool place(Tile* tile);
	Tile* getCurrentTile();
	bool isClicked(Event event);
	void handleClick();
};

