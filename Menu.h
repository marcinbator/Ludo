#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;
class Team;

class Menu
{
	int players;
	int si;
	void initMenu();

public:
	Menu();

	void showWinners(Team** teams, int players);

	int getPlayers();
	int getSi();
};

