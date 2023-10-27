#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Board.h"

using namespace std;
class Tile;
class Team;

class Pawn
{
	int id{};
	bool isAtBase;
	bool isAtTarget;
	Team* team;
	Tile* currentTile;
	sf::Texture texture;
	sf::Sprite sprite;
public:

	Pawn() = delete;
	Pawn(int id, Team* team, Tile* currentTile);

	void draw(Tile* tile, sf::RenderWindow* window);
	bool handleClick(int dice, sf::RenderWindow* window, Board* board);
	void setAtBase(sf::RenderWindow* window, Board* board);
	void setIsAtBase(bool isAtBase);

	int getId() const;
	Team* getTeam();
	Tile* getCurrentTile();
	bool getIsAtBase() const;
	bool getIsAtTarget() const;
	bool isClicked(sf::Event event) const;
	bool canMoveFurther(int tiles, Board* board);
private:
	void initSprite();
	bool move(Tile* tile, sf::RenderWindow* window, Board* board);
	bool deploy(int dice, sf::RenderWindow* window, Board* board);
	int getNextTileId(int currentId);
	void checkIsAtTarget();
};

