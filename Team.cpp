#include "Team.h"

Team::Team(int id, string name,  Tile* startingTile, string texturePath)
{
    this->id = id;
    this->name = name;
    this->texturePath = texturePath;
    this->startingTile = startingTile;
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
