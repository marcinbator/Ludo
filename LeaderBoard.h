#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;
class Button;
class Game;

class LeaderBoard
{
	bool isDisplayed;

	Font font;
	Text leaderboard;

	Button* rematchButton;
	Button* exitButton;

	void initMenu(int centerX, int centerY);
	void drawLogo(RenderWindow* window, int centerX, int centerY);
	void handlePlayerButtonClick(int index);
	void handleAiPlayerButtonClick(int index);

public:
	LeaderBoard(int centerX, int centerY);
	~LeaderBoard();

	void draw(RenderWindow* window, int centerX, int centerY);
	void handleClick(Event event, Game* game);

	bool getIsDisplayed();
};

