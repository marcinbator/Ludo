#pragma once

#include "TeamName.h"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Team
{
	int id;
	TeamName teamName;
	Texture texture;
	int numberWon;
	int place;
	int startTile;
	int baseTilesIds[4];
	int* pawnsIds;
	void asignTeams(TeamName teamName);
public:
	Team() = delete;
	Team(TeamName teamName, int* pawnsIds);
	void addNumberWon();
	void setPlace(int place);
	int getNumberWond();
	int getPlace();
	int getStartTile();
	int* getBaseTilesIds();
	TeamName getTeamName();
	Texture getTexture();
};

