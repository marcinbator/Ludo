#include "Team.h"

Team::Team(TeamName teamName, int* pawnsIds)
{
    this->teamName = teamName;
    this->numberWon = 0;
    this->place = 0;
    this->pawnsIds = pawnsIds;
    asignTeams(teamName);
}

void Team::asignTeams(TeamName teamName)
{
    int baseId = 0;
    switch (teamName) {
    case red: {
        this->id = 1;
        this->texture.loadFromFile("Rpawn");
        this->startTile = 1;
        baseId = 60;
    };
    case blue: {
        this->id = 1;
        this->texture.loadFromFile("Bpawn");
        this->startTile = 11;
        baseId = 70;
    };
    case green: {
        this->id = 1;
        this->texture.loadFromFile("Gpawn");
        this->startTile = 21;
        baseId = 80;
    };
    case yellow: {
        this->id = 1;
        this->texture.loadFromFile("Ypawn");
        this->startTile = 31;
        baseId = 90;
    };
    }
    for (int i = 0; i < 4; i++) {
        this->baseTilesIds[i] = baseId+i;
    }
}

void Team::addNumberWon()
{
    this->numberWon++;
}

void Team::setPlace(int place)
{
    this->place = place;
}

int Team::getNumberWond()
{
    return this->numberWon;
}

int Team::getPlace()
{
    return this->place;
}

int Team::getStartTile()
{
    return this->startTile;
}

int* Team::getBaseTilesIds()
{
    return this->baseTilesIds;
}

TeamName Team::getTeamName()
{
    return this->teamName;
}

Texture Team::getTexture()
{
    return this->texture;
}
