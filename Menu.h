#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Menu
{
	int players;
	int si;
	void initMenu();

public:
	Menu();

	int getPlayers();
	int getSi();
};

