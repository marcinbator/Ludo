#include "Game.h"
#include "InitialMenu.h"
#include "LeaderBoard.h"
#include "Random.h"
#include <thread>
#include <chrono>

Game::Game()
{
    this->currentFreePodiumPlace = 1;
    this->initWindow();
    this->board = new Board(window);
    this->leaderBoard = new LeaderBoard(this->board->getCenterX(), this->board->getCenterY());
    this->menu = new InitialMenu(this->board->getCenterX(), this->board->getCenterY());
    this->dice = 0;
}

Game::~Game()
{
    delete this->window;
    delete this->board;
    delete this->tossButton;
    delete this->dial;
    delete this->menu;
    delete this->leaderBoard;
    for (int i = 0; i < this->playersTotalAmount; i++) {
        delete this->teams[i];
    }
    for (int i = 0; i < this->playersTotalAmount * 4; i++) {
        delete this->pawns[i];
    }
}


void Game::update(bool& restart)
{
    this->window->setFramerateLimit(60);
    if (this->menu->getIsDisplayed()) {
        this->pollMenuEvents();
    }
    else if (this->leaderBoard->getIsDisplayed()) {
        this->pollLeaderboardEvents(restart);
    }
    else {
        this->pollEvents();
        if (this->teams[this->currentTeamId]->getIsAi()) {
            this->tossButton->canToss = false;
            this->dice = random(1, 6);
            this->ai.move(this->teams[this->currentTeamId], this->dice, this->window, this->board);
            if (this->teams[this->currentTeamId]->isWin()) { //check win
                this->handleSingleWin();
            }
            this_thread::sleep_for(chrono::milliseconds(300));
            this->dice = 0;
            this->tossButton->canToss = true;
            this->getNextTeamId();
        }
    }    
}

void Game::render()
{
    if (this->menu->getIsDisplayed()) {
        this->window->clear();
        this->menu->draw(this->window, this->board->getCenterX(), this->board->getCenterY());
        this->window->display();
    }
    else if (this->leaderBoard->getIsDisplayed()) {
        this->window->clear();
        this->leaderBoard->draw(this->window, this->board->getCenterX(), this->board->getCenterY());
        this->window->display();
    }
    else {
        this->window->clear();
        this->board->drawBoard(this->window);
        this->dial->draw(this->window);
        this->renderPawns();
        if (this->tossButton->canToss) {
            this->tossButton->draw(this->window);
        }
        this->window->display();
    }
}

bool Game::isRunning()
{
    return this->window->isOpen();
}

//private

void Game::initWindow() {
    this->window = new RenderWindow(VideoMode(900, 900), "Ludo", Style::Titlebar | Style::Close);
    Image icon;
    icon.loadFromFile("images/logo.png");
    this->window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

void Game::initControls()
{
    this->tossButton = new TossButton("RZUT", this->board->getCenterX(), this->board->getCenterY() + 40 * 9);
    this->dial = new Dial("Zaczyna gracz: " + this->teams[this->currentTeamId]->getName(), this->board->getCenterX(), this->board->getCenterY() + 40 * 7);
}

void Game::renderPawns() {
    for (int i = 0; i < this->playersTotalAmount*4; i++) {
        this->pawns[i]->draw(this->pawns[i]->getCurrentTile(), this->window);
    }
}

void Game::createTeams()
{
    this->playersAmount = menu->getPlayersAmount();
    this->aiPlayersAmount = menu->getAiPlayersAmount();
    this->playersTotalAmount = this->playersAmount + this->aiPlayersAmount;
    this->currentTeamId = random(0, playersTotalAmount - 1);

    const string names[] = { "Czerwony", "Niebiski", "Zielony", "Zolty" };
    const string images[] = { "images/Rpawn.png", "images/Bpawn.png", "images/Gpawn.png", "images/Ypawn.png" };
    const int startTiles[] = { 1, 11, 21, 31 };
    const int baseTiles[] = { 101, 111, 121, 131 };

    int menuPlayersIndex = 0; //create players
    for (int i = 0; i < this->playersAmount; i++) {
        for (int j = menuPlayersIndex; j < 4; j++) {
            if (this->menu->getPlayersColors()[j] != "") {
                Team* team = new Team(i + 1, false, names[j], this->board->getTileById(startTiles[j]), images[j]);
                this->teams[i] = team;
                menuPlayersIndex = j+1;
                for (int k = 0; k < 4; k++) {
                    int index = i * 4 + k;
                    int teamIndex = i;
                    int tileId = baseTiles[j] + k;
                    Tile* tile = this->board->getTileById(tileId);
                    Pawn* pawn = new Pawn(index, this->teams[teamIndex], tile);
                    this->pawns[index] = pawn;
                }
                break;
            }
        }
    }
    int menuAiPlayersIndex = 0; //create ai players
    for (int i = this->playersAmount; i < this->playersTotalAmount; i++) {
        for (int j = menuAiPlayersIndex; j < 4; j++) {
            if (this->menu->getAiPlayersColors()[j] != "") {
                Team* team = new Team(i + 1, true, names[j], this->board->getTileById(startTiles[j]), images[j]);
                this->teams[i] = team;
                menuAiPlayersIndex = j + 1;

                for (int k = 0; k < 4; k++) {
                    int index = i * 4 + k;
                    int teamIndex = i;
                    int tileId = baseTiles[j] + k;
                    Tile* tile = this->board->getTileById(tileId);
                    Pawn* pawn = new Pawn(index, this->teams[teamIndex], tile);
                    this->pawns[index] = pawn;
                }
                break;
            }
        }
    }
    for (int i = 0; i < this->playersTotalAmount; i++) { //assign pawns to teams
        Pawn* subpawns[] = { this->pawns[i * 4],
            this->pawns[i * 4 + 1],
            this->pawns[i * 4 + 2],
            this->pawns[i * 4 + 3] };
        this->teams[i]->setPawns(subpawns);
    }

    this->initControls();
    std::cout << "Game loaded successfully.\nPlayers: " << this->playersAmount + this->aiPlayersAmount << endl;
    std::cout << "Current player: " << this->teams[this->currentTeamId]->getName() << endl;
    //debug
    for (int i = 0; i < 4; i++) {
        this->pawns[i]->draw(this->board->getTileById(40 - i), this->window);
        this->pawns[i]->setIsAtBase(false);
    }
}

void Game::handleTossClick() {
    this->tossButton->handleClick(this->dice);
    this->dial->setText("Kostka: " + to_string(this->dice) + ". Ruch gracza: " + this->teams[this->currentTeamId]->getName());
    this->tossButton->canToss = false;
    if (this->teams[currentTeamId]->areAllObstructed(this->dice, this->board)) { //player is obstructed
        this->handleAllObstructed();
        return;
    }
    cout << "Current player: " << this->teams[this->currentTeamId]->getName()<<endl;
}

void Game::handlePawnClick(int pawnId) {
    if (this->pawns[pawnId]->getTeam()->getId() == 1 + this->currentTeamId) { //pawn of correct team clicked
        if (this->pawns[pawnId]->handleClick(this->dice, this->window,this->board)) { //if move is possible -> move itself
            this->dice = 0;
            this->tossButton->canToss = true;
            if (this->teams[this->currentTeamId]->isWin()) { //check win
                this->handleSingleWin();
            }
            this->getNextTeamId(); //get next or detect game ends
        }
    }
    else {
        this->dial->setText("Blad! Teraz ruch gracza " + this->teams[this->currentTeamId]->getName());
    }
}

void Game::getNextTeamId()
{
    int id = this->currentTeamId;
    int attempts = 0;
    int won = 0;
    for (int i = 0; i < this->playersTotalAmount; i++) {
        if (this->teams[i]->isWin()) { //count won
            won++;
        }
    }
    if (won == this->playersTotalAmount - 1) { //end of the game - one player left
        this->handleGameEnd();
        return;
    }
    do {
        id = (id + 1) % this->playersTotalAmount;
        attempts++;
    } while (this->teams[id]->isWin() && attempts < this->playersTotalAmount);
    if (attempts >= this->playersTotalAmount) { //no valid player found
        this->currentTeamId = id+10;
        return;
    }
    this->currentTeamId = id;
    this->dial->setText("Rzut gracza " + this->teams[this->currentTeamId]->getName());
}

void Game::handleAllObstructed()
{
    this->dial->setText("\nKostka: " + to_string(this->dice) + ". Gracz zablokowany");
    this->dial->draw(this->window);
    this->window->display();
    this_thread::sleep_for(chrono::seconds(1));
    this->getNextTeamId();
    this->tossButton->canToss = true;
    this->dial->setText("Kostka: " + to_string(this->dice) + ". Rzuca gracz " + this->teams[this->currentTeamId]->getName());
}

void Game::handleSingleWin()
{
    this->dial->setText("\nZwycieza gracz " + this->teams[this->currentTeamId]->getName() + "!");
    this->dial->draw(this->window);
    this->window->display();
    this->teams[this->currentTeamId]->setStanding(this->currentFreePodiumPlace);
    this->currentFreePodiumPlace++;
    this_thread::sleep_for(chrono::seconds(1));
}

void Game::handleGameEnd()
{
    this->dial->setText("Koniec gry! ");
    this->tossButton->canToss = false;
    this->leaderBoard->setIsDisplayed(true);
    this->leaderBoard->showWinners(this->teams, this->playersTotalAmount);
}

void Game::pollMenuEvents()
{
    Event event;
    while (this->window->pollEvent(event))
    {
        if (event.type == Event::Closed)
        {
            this->window->close();
        }
        else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
        {
            this->menu->handleClick(event, this);
        }
    }
}

void Game::pollLeaderboardEvents(bool& restart)
{
    Event event;
    while (this->window->pollEvent(event))
    {
        if (event.type == Event::Closed)
        {
            this->window->close();
        }
        else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
        {
            this->leaderBoard->handleClick(event, this, this->window, restart);
        }
    }
}

void Game::pollEvents()
{
    Event event;
    while (this->window->pollEvent(event))
    {
        if (event.type == Event::Closed)
        {
            this->window->close();
        }
        else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
        {
            for (int i = 0; i < 72; i++)
            {
                Tile* tile = this->board->getTiles()[i];
                if (tile->isClicked(event)) {
                    tile->handleClick();
                }
            }
            for (int i = 0; i < this->playersTotalAmount*4; i++) {
                if (pawns[i]->isClicked(event)) {
                    this->handlePawnClick(i);
                }
            }
            if (this->tossButton->isClicked(event) && this->tossButton->canToss) {
                this->handleTossClick();
            }
        }
    }
}