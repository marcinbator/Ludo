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
    delete this->tossButton;
    delete this->dial;
    delete this->initialMenu;
    delete this->leaderBoard;
    delete this->board;
    for (int i = 0; i < this->playersTotalAmount; i++) {
        delete this->teams[i];
    }
    for (int i = 0; i < this->playersTotalAmount * 4; i++) {
        delete this->pawns[i];
    }
    delete this->window;
}

void Game::update()
{
    if (this->initialMenu->getIsDisplayed()) { //initialMenu active
        this->initialMenu->pollMenuEvents(this->window, this, this->restart);
    }
    else if (this->leaderBoard->getIsDisplayed()) { //leaderboard active
        this->leaderBoard->pollEvents(this->window, this, this->restart);
    }
    else { //game active
        this->pollEvents();
        if (this->teams[this->currentTeamId]->getIsAi()) {
            this->handleAiMove();
        }
    }    
}

void Game::render()
{
    if (this->initialMenu->getIsDisplayed()) {
        this->window->clear();
        this->initialMenu->draw(this->window, this->board->getCenterX(), this->board->getCenterY());
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

bool Game::isRunning() const
{
    return this->window->isOpen();
}

//private
void Game::initWindow() {
    this->window = new RenderWindow(VideoMode(1200, 920), "Ludo", Style::Titlebar | Style::Close);
    this->window->setFramerateLimit(60);
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
    this->ai = new Ai(this->initialMenu->getLevel());
    this->playersAmount = initialMenu->getPlayersAmount();
    this->aiPlayersAmount = initialMenu->getAiPlayersAmount();
    this->playersTotalAmount = this->playersAmount + this->aiPlayersAmount;
    this->currentTeamId = random(0, playersTotalAmount - 1);

    const string names[] = { "Czerwony", "Niebiski", "Zielony", "Zolty" };
    const string images[] = { "images/Rpawn.png", "images/Bpawn.png", "images/Gpawn.png", "images/Ypawn.png" };
    const string aiImages[] = { "images/RpawnAI.png", "images/BpawnAI.png", "images/GpawnAI.png", "images/YpawnAI.png" };
    const int startTiles[] = { 1, 11, 21, 31 };
    const int baseTiles[] = { 101, 111, 121, 131 };

    int menuPlayersIndex = 0; //create players
    for (int i = 0; i < this->playersAmount; i++) {
        for (int j = menuPlayersIndex; j < 4; j++) {
            if (this->initialMenu->getPlayersColors()[j] != "") {
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
            if (this->initialMenu->getAiPlayersColors()[j] != "") {
                Team* team = new Team(i + 1, true, names[j], this->board->getTileById(startTiles[j]), aiImages[j]);
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
    ////debug
    //for (int i = 0; i < 4; i++) {
    //    this->pawns[i]->draw(this->board->getTileById(40 - i), this->window);
    //    this->pawns[i]->setIsAtBase(false);
    //}
}

void Game::handleAiMove() {
    this->tossButton->handleClick(this->dice, this->board);
    this->delayClock.restart();
    while (this->delayClock.getElapsedTime().asMilliseconds() < this->delayTime * 2) {
        this->tossButton->canToss = false;
        this->dial->setText("Kostka: " + to_string(this->dice) + ". Ruch gracza: " + this->teams[this->currentTeamId]->getName());
        this->render();
        this->pollEvents();
    }
    if (!this->ai->move(this->teams[this->currentTeamId], this->dice, this->window, this->board)) {
        this->dial->setText("Kostka: " + to_string(this->dice) + ". Gracz zablokowany");
        this->delayClock.restart();
        while (this->delayClock.getElapsedTime().asMilliseconds() < this->delayTime) {
            this->render();
            this->pollEvents();
        }
    }
    if (this->teams[this->currentTeamId]->isWin()) { //check win
        this->handleSingleWin();
    }
    this->dice = 0;
    this->setNextTeamId();
    this->delayClock.restart();
    while (this->delayClock.getElapsedTime().asMilliseconds() < this->delayTime) {
        this->render();
        this->pollEvents();
    }
}

void Game::handleTossClick() {
    this->tossButton->handleClick(this->dice, this->board);
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
            this->tossButton->canToss = false;
            if (this->teams[this->currentTeamId]->isWin()) { //check win
                this->handleSingleWin();
            }
            this->setNextTeamId(); //get next or detect game ends
        }
        this->delayClock.restart();
        while (this->delayClock.getElapsedTime().asMilliseconds() < this->delayTime) {
            this->render();
            this->pollEvents();
        }
    }
    else {
        this->dial->setText("Blad! Teraz ruch gracza " + this->teams[this->currentTeamId]->getName());
    }
}

void Game::setNextTeamId()
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
    if (!this->teams[this->currentTeamId]->getIsAi()) {
        this->tossButton->canToss = true;
    }
    this->dial->setText("Rzut gracza " + this->teams[this->currentTeamId]->getName());
}

void Game::handleAllObstructed()
{
    this->dial->setText("Kostka: " + to_string(this->dice) + ". Gracz zablokowany");
    this->delayClock.restart();
    while (this->delayClock.getElapsedTime().asMilliseconds() < this->delayTime) {
        this->render();
        this->pollEvents();
    }
    this->setNextTeamId();
    this->tossButton->canToss = true;
    this->dial->setText("Kostka: " + to_string(this->dice) + ". Rzuca gracz " + this->teams[this->currentTeamId]->getName());
}

void Game::handleSingleWin()
{
    this->dial->setText("Zwycieza gracz " + this->teams[this->currentTeamId]->getName() + "!");
    this->teams[this->currentTeamId]->setStanding(this->currentFreePodiumPlace);
    this->currentFreePodiumPlace++;
    this->delayClock.restart();
    while (this->delayClock.getElapsedTime().asMilliseconds() < this->delayTime) {
        this->render();
        this->pollEvents();
    }
}

void Game::handleGameEnd()
{
    this->dial->setText("Koniec gry! ");
    this->tossButton->canToss = false;
    this->delayClock.restart();
    while (this->delayClock.getElapsedTime().asMilliseconds() < this->delayTime) {
        this->render();
        this->pollEvents();
    }
    this->leaderBoard->setIsDisplayed(true);
    this->leaderBoard->showWinners(this->teams, this->playersTotalAmount);
}

void Game::pollEvents()
{
    Event event;
    while (this->window->pollEvent(event))
    {
        if (event.type == Event::Closed)
        {
            this->restart = false;
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
            if (this->board->getWarp()->isClicked(event)) {
                this->isWarp = !this->isWarp;
                string texture = this->isWarp ? "images/unwarp.png": "images/warp.png";
                this->delayTime = this->isWarp ? 100 : 800;
                this->board->getWarp()->setTexture(texture);
            }
            if (this->board->getRematch()->isClicked(event)) {
                this->restart = true;
                window->close();
            }
        }
    }
}