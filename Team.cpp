#include "Team.h"

Team::Team(int id, string name,  Tile* startingTile, string texturePath)
{
    this->id = id;
    this->name = name;
    this->texturePath = texturePath;
    this->startingTile = startingTile;
    this->allAtBase = true;
}

void Team::setPawns(Pawn* pawns[4])
{
    this->pawns = *pawns;
}

Pawn* Team::getPawns()
{
    return this->pawns;
}

string Team::getName()
{
    return this->name;
}

Tile* Team::getStartingTile()
{
    return this->startingTile;
}

string Team::getTexturePath()
{
    return this->texturePath;
}

bool Team::isAllAtBase()
{
    int atBase = 0;
    for (int i = 0; i < 4; i++) {
        if (this->pawns[i].getIsAtBase()) {
            atBase++;
        }
    }
    if (atBase == 4) {
        this->allAtBase = true;
        return true;
    }
    this->allAtBase = false;
    return false;
}
