#include "Pawn.h"
#include "Tile.h"
#include "Team.h"
#include "Board.h"

Pawn::Pawn(int id, Team* team, RenderWindow* window, Tile* currentTile, Board* board)
{
	this->id = id;
	this->team = team;
	this->currentTile = currentTile;
	this->window = window;
	this->board = board;
	this->isAtBase = true;
	this->isAtTarget = false;
	initSprite();
}

void Pawn::draw(Tile* tile)
{
	this->currentTile->setCurrentPawn(nullptr);
	this->sprite.setPosition(tile->getPositionX(), tile->getPositionY());
	this->window->draw(this->sprite);
	this->currentTile = tile;
	this->currentTile->setCurrentPawn(this);
	this->checkIsAtTarget();
}

bool Pawn::move(Tile* tile)
{
	if (tile->getCurrentPawn() != nullptr) { //desired tile occupied
		if (tile->getCurrentPawn()->team == this->team) { //tile occupied by teammate
			return false;
		}
		tile->getCurrentPawn()->setAtBase(); //strike
	}
	this->draw(tile);
	return true;
}

void Pawn::setAtBase()
{
	int tileId = this->team->getStartingTile()->getId() + Board::BASE_FIRST_ID; //first base tile id
	Tile* tile = this->board->getTileById(tileId);
	for (int i = 0; i < Board::BASE_SIZE; i++) {
		if (this->move(tile)) { //desired base tile is free
			break;
		}
		tileId++; //get next base tile
		tile = this->board->getTileById(tileId);
	}
	this->isAtBase = true;
}

bool Pawn::handleClick(int& dice, bool& canToss)
{
	if (this->isAtBase){ //deploy desired
		return deploy(dice, canToss);
	}
	if (this->canMoveFurther(dice)) { //pawn move not exceeding its route
		int nextId = this->currentTile->getId();
		for (int i = 0; i < dice; i++) { //get desired tile
			nextId = this->getNextTileId(nextId);
		}
		if (this->move(this->board->getTileById(nextId))) { //move possible
			dice = 0;
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
	return this->team;
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

bool Pawn::getIsAtTarget()
{
	return this->isAtTarget;
}

//private

bool Pawn::deploy(int& dice, bool& canToss)
{
	if (dice == 1 || dice == 6) { //deploy condition 
		if (this->move(this->team->getStartingTile())) { //deploy possible
			dice = 0;
			canToss = true;
			this->isAtBase = false;
			return true;
		}
	}
	//canToss = true; //deploy not possible
	return false;
}

int Pawn::getNextTileId(int currentId) {
	int nextId = currentId;
	if (currentId == this->team->getStartingTile()->getId() - 1 || (this->team->getStartingTile()->getId() == 1 && currentId == Board::LAST_TILE)) { //pawn at target-turning tile
		nextId = this->team->getStartingTile()->getId() + Board::BASE_DISTANCE;
	}
	else if (currentId == Board::LAST_TILE) { //pawn at end of board
		nextId = 1;
	}
	else if(currentId != this->team->getStartingTile()->getId() + Board::BASE_DISTANCE_END){ //pawn not at the end of its route
		nextId++;
	}
	return nextId;
}

bool Pawn::canMoveFurther(int tiles) {
	return this->currentTile->getId() + tiles <= this->team->getStartingTile()->getId() + Board::BASE_DISTANCE_END; //if pawn next move not exceed its route
}

void Pawn::checkIsAtTarget()
{
	if (this->currentTile->getId() > this->team->getStartingTile()->getId() + Board::BASE_DISTANCE
		&& this->currentTile->getId() < this->team->getStartingTile()->getId() + Board::BASE_DISTANCE_END+1) 
	{
		this->isAtTarget = true;
	}
}

void Pawn::initSprite()
{
	this->texture.loadFromFile(this->team->getTexturePath());
	this->sprite.setTexture(this->texture);
	this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);
}