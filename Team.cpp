#include "Team.h"
#include "Board.h"

Team::Team(int id, string name,  Tile* startingTile, string texturePath)
{
    this->id = id;
    this->name = name;
    this->texturePath = texturePath;
    this->startingTile = startingTile;
    cout << "Team " + this->name << " created successfully.\n";
}

Team::~Team()
{
    delete[] this->pawns;
}

void Team::setPawns(Pawn* pawns[4])
{
    for (int i = 0; i < 4; i++) {
        this->pawns[i] = pawns[i];
    }
}

Pawn** Team::getPawns()
{
    return this->pawns;
}

string Team::getName()
{
    return this->name;
}

int Team::getId()
{
    return this->id;
}

Tile* Team::getStartingTile()
{
    return this->startingTile;
}

string Team::getTexturePath()
{
    return this->texturePath;
}

bool Team::areAllObstructed(int dice, Board* board)
{
    int obstructed = 0;
    for (int i = 0; i < 4; i++) {
        if ((dice!=1 && dice !=6 && this->pawns[i]->getIsAtBase()) //at base, cannot exit
            || (this->pawns[i]->getIsAtBase() == false && !this->pawns[i]->canMoveFurther(dice, board))){ //not at base, cannot move
            obstructed++;
        }
    }
    return obstructed == 4;
}

bool Team::isWin()
{
    int atTarget = 0;
    for (int i = 0; i < 4; i++) {
        if (this->pawns[i]->getIsAtTarget()) {
            atTarget++;
        }
    }
    return atTarget == 4;
}
