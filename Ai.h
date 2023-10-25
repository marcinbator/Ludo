#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
class Board;
class Team;

class Ai
{
	int pawnToMoveId;
	int level;
	Team* team;
public:
	Ai() = delete;
	Ai(int level);

	void move(Team* team, int dice, RenderWindow* window, Board* board);
	void setPawnToMoveId();
};

