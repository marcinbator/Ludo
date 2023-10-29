#include "Ai.h"
#include "Game.h"
#include "Team.h"
#include "Board.h"

Ai::Ai(int level, Team* team, Board* board)
{
	this->level = level;
	this->team = team;
	this->board = board;
	cout << "level:"<< level << endl;
}

bool Ai::move(int dice, sf::RenderWindow* window)
{
	this->dice = dice;
	if (this->decide() != 0) {
		this->team->getPawns()[this->decide()]->handleClick(dice, window, this->board);
		return true;
	}
	return false;
}

int Ai::decide()
{
	auto possible = this->getPossibleMoves();
	while (possible.size() > 1) {
		possible = this->checkStrike(possible);
		possible = this->selectFromDice(possible);
	}
	if (possible.size() == 0) {
		return 0;
	}
	return possible.front();
}

vector<int> Ai::getPossibleMoves()
{
	vector<int> possible;
	for (int i = 0; i < Game::PAWNS_TEAM; i++) {
		if (this->team->getPawns()[i]->canMove(this->dice, this->board)) {
			possible.push_back(i);
			cout << i;
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
			newPossible.push_back(i);
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
				newNewPossible.push_back(i);
			}
		}
		return newNewPossible;
	}
	else if (newPossible.size() == 1) {
		return newPossible;
	}
	return possible;
}

vector<int> Ai::selectFromDice(vector<int> possible)
{
	int maxDistance = 0;
	int maxDistanceId = 0;
	vector<int> newPossible;
	for (int i = 0; i < possible.size(); i++) {
		int distance = this->team->getPawns()[possible.at(i)]->getDistanceFromStart(this->board);
		if (distance > maxDistance) {
			maxDistance = distance;
			maxDistanceId = i;
		}
	}
	if (this->dice < 3) {
		newPossible.push_back(possible.front());
		return newPossible;
	}
	newPossible.push_back(maxDistanceId);
	return newPossible;
}

void Ai::setNextPawnId()
{
	this->pawnToMoveId++;
	if (this->pawnToMoveId > Game::PAWNS_TEAM-1) {
		this->pawnToMoveId = 0;
	}
}
