#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
class Board;
class Team;

class Ai
{
	int pawnToMoveId;
	Team* team;
public:
	Ai();

	void move(Team* team, int dice, RenderWindow* window, Board* board);
	void setPawnToMoveId();
};

