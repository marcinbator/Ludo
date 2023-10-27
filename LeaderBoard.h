#pragma once
#include "Menu.h"
#include "Game.h"
#include "Team.h"

using namespace std;

class Button;

class LeaderBoard : public Menu
{
	Button* rematchButton;
	Button* exitButton;
	sf::Text leaderboard;
public:
	LeaderBoard() = delete;
	LeaderBoard(int centerX, int centerY);
	~LeaderBoard();

	void draw(sf::RenderWindow* window, int centerX, int centerY);
	void setIsDisplayed(bool isDisplayed);
	void showWinners(Team** teams, int livePlayersAmount);
	void pollEvents(sf::RenderWindow* window, Game* game, bool& restart);
private:
	void initTitle(int centerX, int centerY);
	void handleRematchButtonClick(Game* game, sf::RenderWindow* window, bool& restart);
	void handleExitButtonClick(sf::RenderWindow* window, bool& restart);
};