#include "Team.h"
#include "Ai.h"

Team::Team(int id, bool isAi, string name,  Tile* startingTile, string texturePath, int level, Board* board)
{
    this->id = id;
    this->name = name;
    this->isAi = isAi;
    this->texturePath = texturePath;
    this->startingTile = startingTile;
    if (this->isAi) {
        this->ai = new Ai(level, this, board);
    }
    else {
        this->ai = nullptr;
    }
    cout << "Team " + this->name << " created successfully.\n";
}

Team::~Team()
{
    if(this->ai != nullptr)
        delete this->ai;
}

void Team::setId(int id)
{
    this->id = id;
}

void Team::setPawns(Pawn* pawns[Game::PAWNS_TEAM])
{
    for (int i = 0; i < 4; i++) {
        this->pawns[i] = pawns[i];
    }
}

void Team::setStanding(int standing)
{
    this->standing = standing;
}

void Team::setPrime(int prime)
{
    this->prime = prime;
}

int Team::getId() const
{
    return this->id;
}

int Team::getPrime() const
{
    return this->prime;
}

int Team::getIsPossibleMovesOne(int dice, Board* board) const
{
    int moves = 0;
    int id = 0;
    for (int i = 0; i < Game::PAWNS_TEAM; i++) {
        if (this->pawns[i]->canMove(dice, board)) {
            moves++;
            id = this->pawns[i]->getId();
        }
    }
    if (moves == 1) {
        return id;
    }
    return -1;
}

string Team::getName() const
{
    return this->name;
}

bool Team::getIsAi() const
{
    return this->isAi;
}

Ai* Team::getAi()
{
    return this->ai;
}

Pawn** Team::getPawns()
{
    return this->pawns;
}

int Team::getStanding() const
{
    return this->standing;
}

Tile* Team::getStartingTile()
{
    return this->startingTile;
}

string Team::getTexturePath() const
{
    return this->texturePath;
}

bool Team::isWin() const
{
    int atTarget = 0;
    for (int i = 0; i < 4; i++) {
        if (this->pawns[i]->getIsAtTarget()) {
            atTarget++;
        }
    }
    return atTarget == Game::PAWNS_TEAM;
}

bool Team::areAllObstructed(int dice, Board* board) const
{
    int obstructed = 0;
    for (int i = 0; i < 4; i++) {
        if (!this->pawns[i]->canMove(dice, board)) {
            obstructed++;
        }
    }
    return obstructed == Game::PAWNS_TEAM;
}