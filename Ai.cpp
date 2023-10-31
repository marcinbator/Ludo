#include "Ai.h"
#include "Game.h"
#include "Team.h"
#include "Board.h"

Ai::Ai(int level, Team* team, Board* board)
{
	this->level = level;
	this->team = team;
	this->board = board;
}

bool Ai::move(int dice, sf::RenderWindow* window)
{
	this->dice = dice;
	this->pawnToMoveId = this->decide();
	if(this->pawnToMoveId != -1 && this->team->getPawns()[this->pawnToMoveId]->handleClick(dice, window, this->board))
		return true;
	return false;
}

int Ai::decide()
{
	auto possible = this->getPossibleMoves(); //all possible moves
	if (possible.size() == 0) //no possible moves
		return 0;
	if (this->level == 1) { //'thinking' level
		while (possible.size() > 1) {
			possible = this->checkStrike(possible);
			if (possible.size() > 1) {
				possible = this->selectIfDeploy(possible);
			}
			if (possible.size() > 1) {
				possible = this->selectFromDice(possible);
			}
		}
	}
	return this->getRandom(possible); //random level
}

vector<int> Ai::getPossibleMoves()
{
	vector<int> possible;
	for (int i = 0; i < Game::PAWNS_TEAM; i++) {
		if (this->team->getPawns()[i]->canMove(this->dice, this->board)) {
			possible.push_back(i);
		}
	}
	return possible;
}

vector<int> Ai::checkStrike(vector<int> possible)
{
	vector<int> newPossible;
	for (int i = 0; i < possible.size(); i++) { //get possible strikes
		Tile* desired = this->team->getPawns()[possible.at(i)]->getDesiredTile(this->dice, this->board);
		if (desired->getCurrentPawn() != nullptr && desired->getCurrentPawn()->getTeam() != this->team) {
			newPossible.push_back(i);
		}
	}
	if (newPossible.size() > 1) { //if more than one -> find furthest and strike
		vector<int> newPossible2;
		int maxId = this->getMinMaxDistanceId(newPossible).at(1);
		newPossible2.push_back(maxId);
		return newPossible2;
	}
	else if (newPossible.size() == 1) {
		return newPossible;
	}
	return possible;
}

vector<int> Ai::selectIfDeploy(vector<int> possible)
{
	if (this->dice == 1 || this->dice == 6) {
		vector<int> notAtBase;
		vector<int> atBase;
		vector<int> newPossible;
		for (int i = 0; i < possible.size(); i++) {
			if (!this->team->getPawns()[possible.at(i)]->getIsAtBase() && !this->team->getPawns()[possible.at(i)]->getIsAtTarget()) {
				notAtBase.push_back(possible.at(i));
			}
			else {
				atBase.push_back(possible.at(i));
			}
		}
		if (notAtBase.size() < 2) { //if less than 2 are in game -> deploy
			newPossible.push_back(this->getRandom(atBase));
			return newPossible;
		}
		newPossible.push_back(this->getRandom(notAtBase));
		return newPossible;
	}
	return possible;
}

vector<int> Ai::selectFromDice(vector<int> possible)
{
	vector<int> newPossible;
	int minId = this->getMinMaxDistanceId(possible).at(0);
	int maxId = this->getMinMaxDistanceId(possible).at(1);
	if (this->dice > 2 || this->team->getPawns()[maxId]->getDistanceFromStart(this->board) - Board::LAST_TILE < this->dice) { 
		newPossible.push_back(maxId);
		return newPossible;
	}
	newPossible.push_back(minId);
	return newPossible;
}

int Ai::getRandom(vector<int> possible)
{
	return possible.at(random(0, possible.size()-1));
}

vector<int> Ai::getMinMaxDistanceId(vector<int> possible)
{
	vector<int> distancesFromStart;
	for (int i = 0; i < possible.size(); i++) {
		auto pawn = this->team->getPawns()[possible.at(i)];
		distancesFromStart.push_back(pawn->getDistanceFromStart(this->board));
	}
	int max = 0;
	int maxId;
	int min = Board::LAST_TILE;
	int minId;
	vector<int> minMaxDistance;
	for (int i = 0; i < distancesFromStart.size(); i++) {
		if (distancesFromStart.at(i) > max) {
			max = distancesFromStart.at(i);
			maxId = possible.at(i);
		}
		if (distancesFromStart.at(i) < min) {
			min = distancesFromStart.at(i);
			minId = possible.at(i);
		}
	}
	minMaxDistance.push_back(minId);
	minMaxDistance.push_back(maxId);
	return minMaxDistance;
}

void Ai::setNextPawnId()
{
	this->pawnToMoveId++;
	if (this->pawnToMoveId > Game::PAWNS_TEAM-1) {
		this->pawnToMoveId = 0;
	}
}
