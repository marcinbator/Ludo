#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;
class Team;

class Menu
{
	int playersAmount;
	int aiPlayersAmount;
	void initMenu();

public:
	Menu();

	void showWinners(Team** teams, int playersAmount);

	int getPlayersAmount();
	int getAiPlayersAmount();
};

