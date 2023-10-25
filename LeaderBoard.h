#pragma once
#include "Menu.h"

using namespace sf;
using namespace std;
class Button;
class Game;

class LeaderBoard : public Menu
{
	Text leaderboard;

	Button* rematchButton;
	Button* exitButton;

	void initTitle(int centerX, int centerY);
	void handleRematchButtonClick(Game* game, RenderWindow* window, bool& restart);
	void handleExitButtonClick(RenderWindow* window, bool& restart);

public:

	LeaderBoard(int centerX, int centerY);
	~LeaderBoard();

	void showWinners(Team** teams, int playersAmount);
	void draw(RenderWindow* window, int centerX, int centerY);
	void handleClick(Event event, Game* game, RenderWindow* window, bool& restart);

	void setIsDisplayed(bool isDisplayed);
};

