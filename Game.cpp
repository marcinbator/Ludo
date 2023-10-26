#include "Game.h"
#include "Board.h"
#include "Team.h"
#include "Pawn.h"
#include "TossButton.h"
#include "Dial.h"
#include "Ai.h"
#include "InitialMenu.h"
#include "LeaderBoard.h"

Game::Game(bool& restart): restart(restart)
{
    this->restart = restart;
    this->initWindow();
    this->board = new Board(window);
    this->initialMenu = new InitialMenu(this->board->getCenterX(), this->board->getCenterY());
    this->leaderBoard = new LeaderBoard(this->board->getCenterX(), this->board->getCenterY());
}

Game::~Game()
{
    delete this->ai;
    delete this->initialMenu;
    delete this->leaderBoard;
    delete this->board;
    for (int i = 0; i < this->playersAmount; i++)
        delete this->teams[i];
    for (int i = 0; i < this->playersAmount * 4; i++)
        delete this->pawns[i];
    delete this->window;
}

void Game::update()
{
    if (this->initialMenu->getIsDisplayed()) { //initial menu displayed
        this->initialMenu->pollMenuEvents(this->window, this, this->restart);
    }
    else if (this->leaderBoard->getIsDisplayed()) { //leaderboard displayed
        this->leaderBoard->pollEvents(this->window, this, this->restart);
    }
    else { //game displayed
        this->pollEvents();
        if (this->teams[this->currentTeamId]->getIsAi()) {
            this->handleAiMove();
        }
    }
}

void Game::render()
{
    this->window->clear();
    if (this->initialMenu->getIsDisplayed()) { //draw initial menu
        this->initialMenu->draw(this->window, this->board->getCenterX(), this->board->getCenterY());
    }
    else if (this->leaderBoard->getIsDisplayed()) { //draw leaderboard
        this->leaderBoard->draw(this->window, this->board->getCenterX(), this->board->getCenterY());
    }
    else { //draw game
        this->board->drawBoard(this->window);
        this->renderPawns();
        if (this->board->getTossButton()->canToss) { //toss possible
            this->board->getTossButton()->draw(this->window);
        }
    }
    this->window->display();
}

void Game::initWindow() {
    this->window = new RenderWindow(VideoMode(1200, 920), "Ludo", Style::Titlebar | Style::Close);
    this->window->setFramerateLimit(60);
    Image icon;
    icon.loadFromFile("images/logo.png");
    this->window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

void Game::renderPawns() {
    for (int i = 0; i < this->playersAmount*4; i++) {
        this->pawns[i]->draw(this->pawns[i]->getCurrentTile(), this->window);
    }
}

void Game::initGame()
{
    this->livePlayersAmount = initialMenu->getPlayersAmount();
    this->aiPlayersAmount = initialMenu->getAiPlayersAmount();
    this->playersAmount = this->livePlayersAmount + this->aiPlayersAmount;

    const string names[] = { "Czerwony", "Niebiski", "Zielony", "Zolty" };
    const int startTiles[] = { 1, 11, 21, 31 };
    const int baseTiles[] = { 101, 111, 121, 131 };

    this->createLivePlayers(names, baseTiles, startTiles);
    this->createAiPlayers(names, baseTiles, startTiles);

    for (int i = 0; i < this->playersAmount; i++) { //assign pawns to teams
        Pawn* subpawns[] = { this->pawns[i * 4],
            this->pawns[i * 4 + 1],
            this->pawns[i * 4 + 2],
            this->pawns[i * 4 + 3] };
        this->teams[i]->setPawns(subpawns);
    }

    this->currentTeamId = random(0, playersAmount - 1);
    if (this->aiPlayersAmount > 0) {
        this->ai = new Ai(this->initialMenu->getLevel());
    }
    this->board->getDial()->setText("Zaczyna gracz: " + this->teams[this->currentTeamId]->getName());

    cout << "Game loaded successfully.\nPlayers: " << this->livePlayersAmount << "+" << this->aiPlayersAmount << endl;
    cout << "Current player: " << this->teams[this->currentTeamId]->getName() << endl;

    //debug
    //for (int i = 0; i < 4; i++) {
    //    this->pawns[i]->draw(this->board->getTileById(40 - i), this->window);
    //    this->pawns[i]->setIsAtBase(false);
    //}
}

void Game::createLivePlayers(const string* names, const int* baseTiles, const int* startTiles)
{
    const string images[] = { "images/Rpawn.png", "images/Bpawn.png", "images/Gpawn.png", "images/Ypawn.png" };
    int menuPlayersUsed = 0;
    for (int i = 0; i < this->livePlayersAmount; i++) {
        for (int j = menuPlayersUsed; j < this->PAWNS_TEAM; j++) {
            if (this->initialMenu->getPlayersColors()[j] != "") { //player exists
                Team* team = new Team(i + 1, false, names[j], this->board->getTileById(startTiles[j]), images[j]);
                this->teams[i] = team;
                menuPlayersUsed = j + 1;
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
}

void Game::createAiPlayers(const string* names, const int* baseTiles, const int* startTiles)
{
    const string aiImages[] = { "images/RpawnAI.png", "images/BpawnAI.png", "images/GpawnAI.png", "images/YpawnAI.png" };
    int menuAiPlayersUsed = 0;
    for (int i = this->livePlayersAmount; i < this->playersAmount; i++) {
        for (int j = menuAiPlayersUsed; j < 4; j++) {
            if (this->initialMenu->getAiPlayersColors()[j] != "") {  //player exists
                Team* team = new Team(i + 1, true, names[j], this->board->getTileById(startTiles[j]), aiImages[j]);
                this->teams[i] = team;
                menuAiPlayersUsed = j + 1;
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
}

void Game::handleAiMove() {
    this->board->getTossButton()->handleClick(this->dice, this->board);
    this->board->getTossButton()->canToss = false;
    this->delay(this->delayTime * 2,
        "Kostka: " + to_string(this->dice) + ". Ruch gracza: " + this->teams[this->currentTeamId]->getName());
    if (!this->ai->move(this->teams[this->currentTeamId], this->dice, this->window, this->board)) { //move not possible
        this->board->getDial()->setText("Kostka: " + to_string(this->dice) + ". Gracz zablokowany");
        this->delay(this->delayTime, "");
    }
    if (this->teams[this->currentTeamId]->isWin()) { //check win
        this->handleSingleWin();
    }
    this->dice = 0;
    this->setNextTeamId();
    this->delay(this->delayTime, "");
}

void Game::handlePlayerTossClick() {
    this->board->getTossButton()->handleClick(this->dice, this->board);
    this->board->getDial()->setText(
        "Kostka: " + to_string(this->dice) + ". Ruch gracza: " + this->teams[this->currentTeamId]->getName());
    this->board->getTossButton()->canToss = false;
    if (this->teams[currentTeamId]->areAllObstructed(this->dice, this->board)) { //player is obstructed
        this->handleAllObstructed();
        return;
    }
}

void Game::handlePawnClick(int pawnId) {
    if (this->pawns[pawnId]->getTeam()->getId() == 1 + this->currentTeamId) { //pawn of correct team clicked
        if (this->pawns[pawnId]->handleClick(this->dice, this->window,this->board)) { //if move is possible -> move itself
            this->dice = 0;
            this->board->getTossButton()->canToss = false;
            if (this->teams[this->currentTeamId]->isWin()) { //check win
                this->handleSingleWin();
            }
            this->setNextTeamId(); //get next or detect game ends
        }
        this->delay(this->delayTime, "");
    }
    else {
        this->board->getDial()->setText("Blad! Teraz ruch gracza " + this->teams[this->currentTeamId]->getName());
    }
}

void Game::setNextTeamId()
{
    int id = this->currentTeamId;
    int attempts = 0;
    int won = 0;
    for (int i = 0; i < this->playersAmount; i++) {
        if (this->teams[i]->isWin()) { //count won
            won++;
        }
    }
    if (won == this->playersAmount - 1) { //end of the game - one player left
        this->handleGameEnd();
        return;
    }
    do {
        id = (id + 1) % this->playersAmount;
        attempts++;
    } while (this->teams[id]->isWin() && attempts < this->playersAmount); //search for next player
    this->currentTeamId = id;
    if (!this->teams[this->currentTeamId]->getIsAi()) { //not ai - let player toss
        this->board->getTossButton()->canToss = true;
    }
    this->board->getDial()->setText("Rzut gracza " + this->teams[this->currentTeamId]->getName());
}

void Game::handleAllObstructed()
{
    this->delay(this->delayTime, "Kostka: " + to_string(this->dice) + ". Gracz zablokowany");
    this->setNextTeamId();
    this->board->getTossButton()->canToss = true;
    this->board->getDial()->setText("Kostka: " + to_string(this->dice) + ". Rzuca gracz " + this->teams[this->currentTeamId]->getName());
}

void Game::handleSingleWin()
{
    this->teams[this->currentTeamId]->setStanding(this->currentFreePodiumPlace);
    this->currentFreePodiumPlace++;
    this->delay(this->delayTime * 2, "Zwycieza gracz " + this->teams[this->currentTeamId]->getName() + "!");
}

void Game::handleGameEnd()
{
    this->board->getTossButton()->canToss = false;
    this->delay(this->delayTime * 2, "Koniec gry! ");
    this->leaderBoard->setIsDisplayed(true);
    this->leaderBoard->showWinners(this->teams, this->playersAmount);
}

void Game::delay(int time, string dial) {
    this->delayClock.restart();
    while (this->delayClock.getElapsedTime().asMilliseconds() < time) {
        if (dial != "") {
            this->board->getDial()->setText("");
        }
        this->render();
        this->pollEvents();
    }
}

void Game::pollEvents()
{
    Event event;
    while (this->window->pollEvent(event))
    {
        if (event.type == Event::Closed) //close window
        {
            this->restart = false;
            this->window->close();
        }
        else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) //mouse click
        {
            for (int i = 0; i < 72; i++) //tiles clicks
            {
                Tile* tile = this->board->getTiles()[i];
                if (tile->isClicked(event)) {
                    tile->handleClick();
                }
            }
            for (int i = 0; i < this->playersAmount*4; i++) { //pawns clicks
                if (pawns[i]->isClicked(event)) {
                    this->handlePawnClick(i);
                }
            }
            if (this->board->getTossButton()->isClicked(event) && this->board->getTossButton()->canToss) { //toss click
                this->handlePlayerTossClick();
            }
            if (this->board->getWarp()->isClicked(event)) { //warp click
                this->isWarp = !this->isWarp;
                string texture = this->isWarp ? "images/unwarp.png": "images/warp.png";
                this->delayTime = this->isWarp ? 100 : 800;
                this->board->getWarp()->setTexture(texture);
            }
            if (this->board->getRematch()->isClicked(event)) { //rematch click
                this->restart = true;
                window->close();
            }
        }
    }
}