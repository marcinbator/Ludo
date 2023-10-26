#include "LeaderBoard.h"
#include "Dial.h"
#include "Team.h"
#include "Game.h"

void LeaderBoard::initTitle(int centerX, int centerY)
{
    this->title.setString("Koniec gry");
    this->title.setOrigin(this->title.getGlobalBounds().width / 2, this->title.getGlobalBounds().height / 2);
    this->title.setPosition(centerX, centerY - 200);
}


void LeaderBoard::handleRematchButtonClick(Game* game, RenderWindow* window, bool& restart)
{
    cout << "Rematch\n";
    restart = true;
    window->close();
}

void LeaderBoard::handleExitButtonClick(RenderWindow* window, bool& restart)
{
    cout << "Exit\n";
    restart = false;
    window->close();
}

void LeaderBoard::pollEvents(RenderWindow* window, Game* game, bool& restart)
{
    Event event;
    while (window->pollEvent(event))
    {
        if (event.type == Event::Closed)
        {
            restart = false;
            window->close();
        }
        else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
        {
            this->handleClick(event, game, window, restart);
        }
    }
}

LeaderBoard::LeaderBoard(int centerX, int centerY)
    : Menu(centerX, centerY)
{
	this->isDisplayed = false;
    this->rematchButton = new Button("Powtórz", "images/button1.png", centerX, centerY + 50);
    this->exitButton = new Button("Wyjdz", "images/button1.png", centerX, centerY + 100);
    initTitle(centerX, centerY);
}

LeaderBoard::~LeaderBoard()
{
    delete this->rematchButton;
    delete this->exitButton;
}

void LeaderBoard::showWinners(Team** teams, int livePlayersAmount)
{
    string text = "";
    Team* leaderboard[4];
    for (int i = 0; i < livePlayersAmount; i++) {
        if (teams[i]->getStanding() != 0) {
            leaderboard[teams[i]->getStanding() - 1] = teams[i];
        }
        else {
            leaderboard[livePlayersAmount - 1] = teams[i];
        }
    }
    for (int i = 0; i < livePlayersAmount; i++) {
        text += "Miejsce " + to_string(i + 1) + ": " + leaderboard[i]->getName() + "\n";
    }
    this->dial->setText(text);
}

void LeaderBoard::draw(RenderWindow* window, int centerX, int centerY)
{
    window->draw(this->title);
    this->drawLogo(window, centerX, centerY);
	this->dial->draw(window);
    this->rematchButton->draw(window);
    this->exitButton->draw(window);
}

void LeaderBoard::handleClick(Event event, Game* game, RenderWindow* window, bool& restart)
{
    if (this->rematchButton->isClicked(event)) {
        this->handleRematchButtonClick(game, window, restart);
    }
    if (this->exitButton->isClicked(event)) {
        this->handleExitButtonClick(window, restart);
    }
}

void LeaderBoard::setIsDisplayed(bool isDisplayed)
{
	this->isDisplayed = isDisplayed;
}
