#include "Pawn.h"
#include "Tile.h"
#include "Team.h"
#include "Board.h"

Pawn::Pawn(int id, Team* team, RenderWindow* window, Tile* currentTile, Board* board)
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
	this->board = board;
}

void Pawn::draw(Tile* tile)
{
	this->currentTile->setCurrentPawn(nullptr);
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
		tile->getCurrentPawn()->setAtBase();
	}
	this->draw(tile);
	return true;
}

void Pawn::setAtBase()
{
	int tileId = this->team->getStartingTile()->getId() + 100;
	Tile* tile = this->board->getTileById(tileId);
	for (int i = 0; i < 4; i++) {
		if (this->move(tile)) {
			break;
		}
		tileId++;
		tile = this->board->getTileById(tileId);
	}
	this->isAtBase = true;
}

bool Pawn::handleClick(int& tiles, bool& canToss)
{
	if (this->isAtBase){
		if (tiles == 1 || tiles == 6) {
			if (this->move(this->team->getStartingTile())) {
				tiles = 0;
				canToss = true;
				this->isAtBase = false;
				return true;
			}
		}
		canToss = true; //check if all in team blocked - todo
		return false;
	}
	if (this->canMoveFurther(tiles)) {
		int nextId = this->currentTile->getId();
		for (int i = 0; i < tiles; i++) {
			nextId = this->getNextTileId(nextId);
		}
		if (this->move(this->board->getTileById(nextId))) {
			tiles = 0;
			canToss = true;
			return true;
		}
	}
	return false;
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

bool Pawn::getIsAtBase()
{
	return this->isAtBase;
}

//private

int Pawn::getNextTileId(int currentId) {
	int nextId = currentId;
	if (currentId == this->team->getStartingTile()->getId()-1 || (this->team->getStartingTile()->getId() == 1 && currentId == 40)) {
		nextId = this->team->getStartingTile()->getId() + 50;
	}
	else if (currentId == 40) {
		nextId = 1;
	}
	else if(currentId!=this->team->getStartingTile()->getId()+53){
		nextId++;
	}
	return nextId;
}

bool Pawn::canMoveFurther(int tiles) {
	return this->currentTile->getId() + tiles <= this->team->getStartingTile()->getId() + 53;
}