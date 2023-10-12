#include "Pawn.h"

Pawn::Pawn(int id, TeamName teamName, RenderWindow* window)
{
	this->id = id;
	this->currentTile = nullptr;
	this->isAtBase = true;
	this->isAtTarget = false;
	this->texture.loadFromFile("images/Rpawn.png");
	this->sprite.setTexture(this->texture);
	this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);
	this->window = window;
}

bool Pawn::draw(Tile* tile)
{
	this->sprite.setPosition(tile->getPositionX(), tile->getPositionY());
	this->window->draw(this->sprite);
	return true;
}

void Pawn::move(int tiles)
{
	
}

void Pawn::deploy()
{
	
}

void Pawn::setInBase()
{

}


Tile* Pawn::getCurrentTile()
{
	return this->currentTile;
}

