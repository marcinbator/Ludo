#include "Team.h"
#include "Board.h"

Team::Team(int id, bool isAi, string name,  Tile* startingTile, string texturePath)
{
    this->id = id;
    this->name = name;
    this->isAi = isAi;
    this->standing = 0;
    this->texturePath = texturePath;
    this->startingTile = startingTile;
    cout << "Team " + this->name << " created successfully.\n";
}

void Team::setPawns(Pawn* pawns[4])
{
    for (int i = 0; i < 4; i++) {
        this->pawns[i] = pawns[i];
    }
}

void Team::setStanding(int standing)
{
    this->standing = standing;
}

int Team::getId()
{
    return this->id;
}

string Team::getName()
{
    return this->name;
}

bool Team::getIsAi()
{
    return this->isAi;
}

Pawn** Team::getPawns()
{
    return this->pawns;
}

int Team::getStanding()
{
    return this->standing;
}

Tile* Team::getStartingTile()
{
    return this->startingTile;
}

string Team::getTexturePath()
{
    return this->texturePath;
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

bool Team::areAllObstructed(int dice, Board* board)
{
    int obstructed = 0;
    for (int i = 0; i < 4; i++) {
        if ((dice!=1 && dice !=6 && this->pawns[i]->getIsAtBase()) //at base, cannot exit
            || (this->pawns[i]->getIsAtBase() == false && !this->pawns[i]->canMoveFurther(dice, board))){ //not at base, cannot move
            obstructed++;
            cout << " Pawn " + to_string(this->pawns[i]->getId()) << " obstructed."<<endl;
        }
    }
    return obstructed == 4;
}