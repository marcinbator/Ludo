#include "Pawn.h"
#include "Tile.h"
#include "Team.h"

Pawn::Pawn(int id, Team* team, RenderWindow* window, Tile* currentTile)
{
	this->id = id;
	this->currentTile = currentTile;
	this->isAtBase = true;
	this->isAtTarget = false;
	this->team = team;
	this->texture.loadFromFile(this->team->getTexturePath());
	this->sprite.setTexture(this->texture);
	this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);
	this->window = window;
}

void Pawn::draw(Tile* tile)
{
	this->sprite.setPosition(tile->getPositionX(), tile->getPositionY());
	this->window->draw(this->sprite);
	this->currentTile = tile;
	this->currentTile->setCurrentPawn(this);
}

bool Pawn::isClicked(Event event) 
{
	if (this->sprite
		.getGlobalBounds()
		.contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
	{
		return true;
	}
	return false;
}

void Pawn::handleClick()
{
	cout << "Pawn: " << this->id << endl;
	this->place(this->team->getStartingTile());
}

void Pawn::move(int tiles)
{
	
}

void Pawn::deploy()
{
	
}

void Pawn::setTeam(Team* team)
{
}

Team* Pawn::getTeam()
{
	return nullptr;
}

void Pawn::setInBase()
{

}

int Pawn::getId()
{
	return this->id;
}

bool Pawn::place(Tile* tile)
{
	if (tile->getCurrentPawn() != nullptr) {
		if (tile->getCurrentPawn()->team == this->team) {
			return false;
		}
	}
	this->draw(tile);
	return true;
}

Tile* Pawn::getCurrentTile()
{
	return this->currentTile;
}

