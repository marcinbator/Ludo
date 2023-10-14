#include "Pawn.h"
#include "Tile.h"
#include "Team.h"

Pawn::Pawn(int id, Team* team, RenderWindow* window, Tile* currentTile)
{
	this->id = id;
	this->team = team;
	this->currentTile = currentTile;
	this->texture.loadFromFile(this->team->getTexturePath());
	this->sprite.setTexture(this->texture);
	this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);
	this->window = window;
	this->isAtBase = true;
	this->isAtTarget = false;
}

void Pawn::draw(Tile* tile)
{
	this->sprite.setPosition(tile->getPositionX(), tile->getPositionY());
	this->window->draw(this->sprite);
	this->currentTile = tile;
	this->currentTile->setCurrentPawn(this);
}

bool Pawn::move(Tile* tile)
{
	if (tile->getCurrentPawn() != nullptr) {
		if (tile->getCurrentPawn()->team == this->team) {
			return false;
		}
	}
	this->draw(tile);
	return true;
}

void Pawn::handleClick()
{
	cout << "Pawn: " << this->id << endl;
	this->move(this->team->getStartingTile());
}

Tile* Pawn::getCurrentTile()
{
	return this->currentTile;
}

Team* Pawn::getTeam()
{
	return nullptr;
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