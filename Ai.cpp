#include "Ai.h"
#include "Game.h"
#include "Team.h"
#include "Board.h"

Ai::Ai(int level, Team* team, Board* board)
{
	this->level = level;
	this->team = team;
	this->board = board;
	cout << "level:" << level << endl;
}

bool Ai::move(int dice, sf::RenderWindow* window)
{
	this->dice = dice;
	this->pawnToMoveId = this->decide();
	if (this->pawnToMoveId != -1 && this->team->getPawns()[this->pawnToMoveId]->handleClick(dice, window, this->board)) {
		return true;
	}
	return false;
}

int Ai::decide()
{
	auto possible = this->getPossibleMoves();
	if (this->level == 1) {
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
	if (possible.size() == 0) {
		return 0;
	}
	return this->getRandom(possible);
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
	for (int i = 0; i < possible.size(); i++) {
		Tile* desired = this->team->getPawns()[possible.at(i)]->getDesiredTile(this->dice, this->board);
		if (desired->getCurrentPawn() != nullptr && desired->getCurrentPawn()->getTeam() != this->team) {
			newPossible.push_back(possible.at(i));
		}
	}
	if (newPossible.size() > 1) {
		vector<int> newNewPossible;
		int maxDistance = 0;
		for (int i = 0; i < newPossible.size(); i++) {
			int distance = this->team->getPawns()[newPossible.at(i)]->getDistanceFromStart(this->board);
			if (distance > maxDistance) {
				maxDistance = distance;
			}
		}
		for (int i = 0; i < newPossible.size(); i++) {
			int distance = this->team->getPawns()[newPossible.at(i)]->getDistanceFromStart(this->board);
			if (distance == maxDistance) {
				newNewPossible.push_back(newPossible.at(i));
			}
		}
		return newNewPossible;
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
		if (notAtBase.size() < 2) {
			newPossible.push_back(this->getRandom(atBase));
			return newPossible;
		}
		for (int i = 0; i < notAtBase.size(); i++) {
			newPossible.push_back(notAtBase.at(i));
		}
		return newPossible;
	}
	return possible;
}

vector<int> Ai::selectFromDice(vector<int> possible)
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
	vector<int> newPossible;
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
	if (this->dice > 2 || Board::LAST_TILE - max < this->dice) {
		newPossible.push_back(maxId);
		return newPossible;
	}
	newPossible.push_back(minId);
	return newPossible;
}

int Ai::getRandom(vector<int> possible)
{
	return possible.at(random(0, possible.size() - 1));
}

void Ai::setNextPawnId()
{
	this->pawnToMoveId++;
	if (this->pawnToMoveId > Game::PAWNS_TEAM - 1) {
		this->pawnToMoveId = 0;
	}
}
