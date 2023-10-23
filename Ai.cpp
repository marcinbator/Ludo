#include "Ai.h"
#include "Random.h"
#include "Board.h"
#include "Team.h"

using namespace sf;

Ai::Ai()
{
	this->pawnToMoveId = 0;
}

void Ai::move(Team* team, int dice, RenderWindow* window, Board* board)
{
	int i = 0;
	Pawn* pawn = team->getPawns()[this->pawnToMoveId];
	do {
		this->setPawnToMoveId();
		pawn = team->getPawns()[this->pawnToMoveId];
		i++;
	} while (!pawn->handleClick(dice, window, board) && i<4);
}

void Ai::setPawnToMoveId()
{
	this->pawnToMoveId++;
	if (this->pawnToMoveId > 3) {
		this->pawnToMoveId = 0;
	}
}