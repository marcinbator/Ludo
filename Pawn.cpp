#include "Pawn.h"

bool Pawn::setPosition(Tile* tile)
{
	return false;
}

Pawn::Pawn(int id, Team* team)
{
	this->id = id;
	this->team = team;
	this->currentTile = nullptr;
	this->isAtBase = true;
	this->isAtTarget = false;
}

void Pawn::move(int tiles)
{
	for (int i = 0; i < tiles; i++) {
		this->setPosition(this->getNextTile());
	}
}

void Pawn::deploy()
{
	Tile tile = this->team->getStartTile();
	this->setPosition(&tile);
}

void Pawn::setInBase()
{
	
}

int Pawn::getId()
{
	return this->id;
}

Tile* Pawn::getCurrentTile()
{
	return this->currentTile;
}

Tile* Pawn::getNextTile()
{
	return nullptr;
}

