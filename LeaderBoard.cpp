#include "LeaderBoard.h"
#include "Button.h"
#include "Dial.h"

LeaderBoard::LeaderBoard(int centerX, int centerY) : Menu(centerX, centerY)
{
	this->isDisplayed = false;
    this->initBackground(centerX, centerY);
    this->rematchButton = new Button("Powtórz", string(TEXTURE_PATH) + "button1.png", centerX, centerY + 50);
    this->exitButton = new Button("Wyjdz", string(TEXTURE_PATH) + "button1.png", centerX, centerY + 100);
    initTitle(centerX, centerY);
}

LeaderBoard::~LeaderBoard()
{
    delete this->rematchButton;
    delete this->exitButton;
}

void LeaderBoard::draw(sf::RenderWindow* window, int centerX, int centerY)
{
    window->draw(this->background);
    this->drawLogo(window, centerX, centerY);
	this->dial->draw(window);
    this->rematchButton->draw(window);
    this->exitButton->draw(window);
    window->draw(this->title);
}

void LeaderBoard::setIsDisplayed(bool isDisplayed)
{
	this->isDisplayed = isDisplayed;
}

void LeaderBoard::showWinners(Team** teams, int livePlayersAmount)
{
    string text = "";
    Team* leaderboard[Game::MAX_TEAMS];
    for (int i = 0; i < livePlayersAmount; i++) {
        if (teams[i]->getStanding() != 0) { //team clasified
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

void LeaderBoard::pollEvents(sf::RenderWindow* window, Game* game, bool& restart)
{
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            restart = false;
            window->close();
        }
        else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            if (this->rematchButton->isClicked(event)) {
                this->handleRematchButtonClick(game, window, restart);
            }
            if (this->exitButton->isClicked(event)) {
                this->handleExitButtonClick(window, restart);
            }
        }
    }
}

void LeaderBoard::initTitle(int centerX, int centerY)
{
    this->title.setString("Koniec gry");
    this->title.setOrigin(this->title.getGlobalBounds().width / 2, this->title.getGlobalBounds().height / 2);
    this->title.setPosition(centerX, centerY - 200);
}


void LeaderBoard::handleRematchButtonClick(Game* game, sf::RenderWindow* window, bool& restart)
{
    cout << "Rematch\n";
    restart = true;
    window->close();
}

void LeaderBoard::handleExitButtonClick(sf::RenderWindow* window, bool& restart)
{
    cout << "Exit\n";
    restart = false;
    window->close();
}