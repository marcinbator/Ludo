#include "Pawn.h"
#include "Tile.h"
#include "Team.h"

Pawn::Pawn(int id, Team* team, Tile* currentTile)
{
	this->id = id;
	this->team = team;
	this->currentTile = currentTile;
	this->isAtBase = true;
	this->isAtTarget = false;
	initSprite();
	cout << "Pawn " + to_string(this->id) + " initialized successfully.\n";
}

void Pawn::draw(Tile* tile, sf::RenderWindow* window)
{
	this->currentTile->setCurrentPawn(nullptr);
	this->sprite.setPosition(tile->getPositionX(), tile->getPositionY());
	this->currentTile = tile;
	this->currentTile->setCurrentPawn(this);
	window->draw(this->sprite);
	if (this->isTargetVisible) {
		window->draw(this->target);
	}
	if (this->isPossibleVisible) {
		window->draw(this->possible);
	}
}

//standard move
bool Pawn::handleClick(int dice, sf::RenderWindow* window, Board* board)
{
	if (this->isAtBase){ //deploy desired
		return deploy(dice, window, board);
	}
	if (this->canMoveFurther(dice, board)) { //pawn move not exceeding its route
		int nextId = this->currentTile->getId();
		for (int i = 0; i < dice; i++) { //get desired tile
			nextId = this->getNextTileId(nextId);
		}
		if (this->move(board->getTileById(nextId), window, board)) { //move possible
			return true;
		}
	}
	return false;
}

void Pawn::handleMouseOver(int dice, sf::RenderWindow* window, Board* board)
{
	if (!this->isAtBase || dice == 1 || dice == 6) {
		int nextId = this->currentTile->getId();
		for (int i = 0; i < dice; i++) { //get desired tile
			nextId = this->getNextTileId(nextId);
		}
		Tile* destination = board->getTileById(nextId);
		if (destination != nullptr) {
			this->targetTexture.loadFromFile(string(TEXTURE_PATH) + "target.png");
			this->target.setTexture(targetTexture);
			this->target.setOrigin(target.getGlobalBounds().width / 2, target.getGlobalBounds().height / 2);
			this->target.setPosition(destination->getPositionX(), destination->getPositionY());
			this->isTargetVisible = true;
		}
	}
}

void Pawn::setTeam(Team* team)
{
	this->team = team;
}

//return current tile to base
void Pawn::setAtBase(sf::RenderWindow* window, Board* board)
{
	int tileId = this->team->getStartingTile()->getId() + Board::BASE_FIRST_ID; //first base tile id
	Tile* tile = board->getTileById(tileId);
	for (int i = 0; i < Board::BASE_SIZE; i++) {
		if (this->move(tile, window, board)) { //desired base tile is free
			break;
		}
		tileId++; //get next base tile
		tile = board->getTileById(tileId);
	}
	this->isAtBase = true;
	cout << "Pawn " + to_string(this->id) + " returned to base.\n";
}

//only for debug - setting on custom fields at the beginning
void Pawn::setIsAtBase(bool isAtBase)
{
	this->isAtBase = isAtBase;
}

void Pawn::setIsTargetVisible(bool isTargetVisible)
{
	this->isTargetVisible = isTargetVisible;
}

bool Pawn::setIsPossibleVisible(int currentTeamId, int dice, sf::RenderWindow* window, Board* board) //highlight possible move
{
	if(this->canMove(dice, board) && currentTeamId == this->team->getId()) {
		this->possibleTexture.loadFromFile(string(TEXTURE_PATH) + "possible.png");
		this->possible.setTexture(possibleTexture);
		this->possible.setOrigin(this->sprite.getOrigin());
		this->possible.setPosition(this->sprite.getPosition());
		this->isPossibleVisible = true;
		return true;
	}
	this->isPossibleVisible = false;
	return false;
}

bool Pawn::canMove(int dice, Board* board)
{
	return ((dice == 1 || dice == 6) && this->isAtBase && this->canMoveFurther(1, board)) || (!this->isAtBase && this->canMoveFurther(dice, board));
}

int Pawn::getId()  const
{
	return this->id;
}

Team* Pawn::getTeam()
{
	return this->team;
}

Tile* Pawn::getCurrentTile()
{
	return this->currentTile;
}

bool Pawn::getIsAtBase() const
{
	return this->isAtBase;
}

bool Pawn::getIsAtTarget() const
{
	return this->isAtTarget;
}

bool Pawn::canMoveFurther(int tiles, Board* board)
{
	int nextId = this->currentTile->getId();
	for (int i = 0; i < tiles; i++) { //get desired tile
		nextId = this->getNextTileId(nextId);
	}
	if (nextId <= this->team->getStartingTile()->getId() + Board::TARGET_LAST_ID) //pawn next move not exceed its route
	{
		Tile* tile = board->getTileById(nextId);
		if (tile != nullptr && tile->getCurrentPawn() != nullptr && tile->getCurrentPawn()->team == this->team) { //pawn tries to move into its team mate
			return false;
		}
		return true;
	}
	return false;
}

void Pawn::initSprite()
{
	this->texture.loadFromFile(this->team->getTexturePath());
	this->sprite.setTexture(this->texture);
	this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);
}

//move with checking possibility on desired tile
bool Pawn::move(Tile* tile, sf::RenderWindow* window, Board* board)
{
	if (tile->getCurrentPawn() != nullptr) { //desired tile occupied
		if (tile->getCurrentPawn()->team == this->team) { //tile occupied by teammate
			cout << "Pawn " + to_string(this->id) + "cannot be placed on tile" + to_string(tile->getId()) << ": occupied by team mate.\n";
			return false;
		}
		cout << "Pawn " + to_string(this->id) + " stroke pawn" + to_string(tile->getCurrentPawn()->getId()) << endl;
		tile->getCurrentPawn()->setAtBase(window, board); //strike
	}
	this->draw(tile, window);
	this->checkIsAtTarget();
	cout << "Pawn " + to_string(this->id) + " placed on tile " + to_string(tile->getId()) << endl;
	return true;
}

bool Pawn::deploy(int dice, sf::RenderWindow* window, Board* board)
{
	if (dice == 1 || dice == 6) { //deploy condition 
		if (this->move(this->team->getStartingTile(), window, board)) { //deploy possible
			this->isAtBase = false;
			cout << "Pawn " + to_string(this->id) + " deployed to game.\n";
			return true;
		}
	}
	return false;
}

int Pawn::getNextTileId(int currentId) {
	int nextId = currentId;
	if (this->isAtBase) {
		nextId = this->team->getStartingTile()->getId();
	}
	else if (currentId == this->team->getStartingTile()->getId() - 1 || (this->team->getStartingTile()->getId() == 1 && currentId == Board::LAST_TILE)) { //pawn at target-turning tile
		nextId = this->team->getStartingTile()->getId() + Board::TARGET_FIRST_ID;
	}
	else if (currentId == Board::LAST_TILE) { //pawn at end of board
		nextId = 1;
	}
	else {
		nextId++;
	}
	return nextId;
}

void Pawn::checkIsAtTarget()
{
	this->isAtTarget = this->currentTile->getId() > this->team->getStartingTile()->getId() + Board::TARGET_FIRST_ID - 1
		&& this->currentTile->getId() < this->team->getStartingTile()->getId() + Board::TARGET_LAST_ID + 1;
	if (this->isAtTarget == true){
		cout << this->id << " is at target." << endl;
	}
}