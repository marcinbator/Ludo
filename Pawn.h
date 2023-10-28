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
	bool isTargetVisible = false;
	bool isPossibleVisible = false;
	Team* team;
	Tile* currentTile;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Texture targetTexture;
	sf::Sprite target;
	sf::Texture possibleTexture;
	sf::Sprite possible;
public:

	Pawn() = delete;
	Pawn(int id, Team* team, Tile* currentTile);

	void draw(Tile* tile, sf::RenderWindow* window);
	bool handleClick(int dice, sf::RenderWindow* window, Board* board);
	void handleMouseOver(int dice, sf::RenderWindow* window, Board* board);
	void setTeam(Team* team);
	void setAtBase(sf::RenderWindow* window, Board* board);
	void setIsAtBase(bool isAtBase);
	void setIsTargetVisible(bool isTargetVisible);
	bool setIsPossibleVisible(int currentTeamId, int dice, sf::RenderWindow* window, Board* board);
	bool canMove(int dice, Board* board);

	int getId() const;
	Team* getTeam();
	Tile* getCurrentTile();
	bool getIsAtBase() const;
	bool getIsAtTarget() const;
	bool canMoveFurther(int tiles, Board* board);
	inline bool isClicked(sf::Event event) const {
		return this->sprite
			.getGlobalBounds()
			.contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
	}
	inline bool isMouseOver(sf::Event event) const {
		return this->sprite
			.getGlobalBounds()
			.contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y));
	}
private:
	void initSprite();
	bool move(Tile* tile, sf::RenderWindow* window, Board* board);
	bool deploy(int dice, sf::RenderWindow* window, Board* board);
	int getNextTileId(int currentId);
	void checkIsAtTarget();
};

