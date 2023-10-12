#include "Player.h"

Player::Player(int id, string name, Pawn* pawns[4], Tile* startingTile)
{
    this->id = id;
    this->name = name;
    this->pawns = *pawns;
    this->startingTile = startingTile;
}

Pawn* Player::getPawns()
{
    return this->pawns;
}

string Player::getName()
{
    return this->name;
}

Tile* Player::getStartingTile()
{
    return this->startingTile;
}
