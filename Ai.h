#pragma once
#include <SFML/Graphics.hpp>
#include "Random.h"
#include "Board.h"
#include "Team.h"

class Ai
{
	int pawnToMoveId;
	int level;
public:
	Ai() = delete;
	Ai(int level);

	bool move(Team* team, int dice, sf::RenderWindow* window, Board* board);
	void setPawnToMoveId();
};

