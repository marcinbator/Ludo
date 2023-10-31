#pragma once
#include <SFML/Graphics.hpp>
#include "Random.h"
#include "Board.h"
#include <vector>

using namespace std;

class Team;
class Board;

class Ai
{
	int level{};
	int dice{};
	int pawnToMoveId{};
	Team* team;
	Board* board;
public:
	Ai() = delete;
	Ai(int level, Team* team, Board* board);
	bool move(int dice, sf::RenderWindow* window);
private:
	int decide();
	vector<int> getPossibleMoves();
	vector<int> checkStrike(vector<int> possible);
	vector<int> selectIfDeploy(vector<int> possible);
	vector<int> selectFromDice(vector<int> possible);
	int getRandom(vector<int> possible);
	void setNextPawnId();
};

