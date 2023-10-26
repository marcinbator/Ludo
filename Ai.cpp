#include "Ai.h"
#include "Game.h"

Ai::Ai(int level)
{
	this->level = level;
	this->pawnToMoveId = 0;
	cout << "level:"<< level << endl;
}

bool Ai::move(Team* team, int dice, RenderWindow* window, Board* board)
{
	int i = 0;
	Pawn* pawn = team->getPawns()[this->pawnToMoveId];
	do {
		this->setPawnToMoveId();
		pawn = team->getPawns()[this->pawnToMoveId];
		i++;
		if (pawn->handleClick(dice, window, board)) {
			return true;
		}
	} while (i<Game::PAWNS_TEAM);
	return false;
}

void Ai::setPawnToMoveId()
{
	this->pawnToMoveId++;
	if (this->pawnToMoveId > Game::PAWNS_TEAM-1) {
		this->pawnToMoveId = 0;
	}
}
