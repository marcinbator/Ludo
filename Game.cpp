#include "Game.h"
#include "Menu.h"
#include "Random.h"
#include <thread>
#include <chrono>

Game::Game()
{
    this->currentFreePodiumPlace = 1;
    this->initWindow();
    this->board = new Board(window);
    this->menu = new Menu(this->board->getCenterX(), this->board->getCenterY());
    this->createTeams();
    this->dice = 0;
    /*this->playersAmount = menu->getPlayersAmount();
    this->aiPlayersAmount = menu->getAiPlayersAmount();
    this->playersTotalAmount = this->playersAmount + this->aiPlayersAmount;
    this->currentTeamId = random(0, playersTotalAmount-1);
    this->initControls();*/
    /*cout << "Game loaded successfully.\nPlayers: " << this->playersAmount + this->aiPlayersAmount << endl;
    cout << "Current player: " << this->teams[this->currentTeamId]->getName() << endl;*/
}

Game::~Game()
{
    delete this->window;
    delete this->board;
    delete this->tossButton;
    delete this->dial;
    for (int i = 0; i < this->playersTotalAmount; i++) {
        delete this->teams[i];
    }
    for (int i = 0; i < this->playersTotalAmount * 4; i++) {
        delete this->pawns[i];
    }
}


void Game::update()
{
    this->window->setFramerateLimit(60);
    if (this->menu->getIsDisplayed()) {
        this->pollMenuEvents();
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
        this->menu->draw(this->window);
        this->window->display();
    }
    else {
        this->playersAmount = menu->getPlayersAmount();
        this->aiPlayersAmount = menu->getAiPlayersAmount();
        this->playersTotalAmount = this->playersAmount + this->aiPlayersAmount;
        this->currentTeamId = random(0, playersTotalAmount - 1);
        this->initControls();
        cout << "Game loaded successfully.\nPlayers: " << this->playersAmount + this->aiPlayersAmount << endl;
        cout << "Current player: " << this->teams[this->currentTeamId]->getName() << endl; 
            //
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
    const string colors[] = { "Czerwony", "Niebieski", "Zielony", "Zolty" };
    const string images[] = { "images/Rpawn.png", "images/Bpawn.png", "images/Gpawn.png", "images/Ypawn.png" };
    const int startTiles[] = { 1, 11, 21, 31 };
    const int baseTiles[] = { 101, 111 - 4, 121 - 8, 131 - 12 };

    for (int i = 0; i < this->playersAmount; i++) {
        Team* team = new Team(i + 1, false, colors[i], this->board->getTileById(startTiles[i]), images[i]);
        this->teams[i] = team;
    }
    for (int i = this->playersAmount; i < this->playersTotalAmount; i++) {
        Team* team = new Team(i + 1, true, colors[i], this->board->getTileById(startTiles[i]), images[i]);
        this->teams[i] = team;
    }
    for (int j = 0; j < this->playersTotalAmount; j++) {
        for (int i = 0; i < 4; i++) {
            int index = j * 4 + i;
            int teamIndex = j;
            int tileId = 101 + j * 10 + i;
            Tile* tile = this->board->getTileById(tileId);
            Pawn* pawn = new Pawn(index, this->teams[teamIndex], tile);
            this->pawns[index] = pawn;
        }
    }
    for (int i = 0; i < this->playersTotalAmount; i++) {
        Pawn* subpawns[] = { this->pawns[i * 4], 
            this->pawns[i * 4 + 1], 
            this->pawns[i * 4 + 2], 
            this->pawns[i * 4 + 3] };
        this->teams[i]->setPawns(subpawns);
        
    }
    //debug
    /*for (int i = 0; i < 4; i++) {
        this->pawns[i]->draw(this->board->getTileById(40 - i), this->window);
        this->pawns[i]->setIsAtBase(false);
    }*/
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
    this_thread::sleep_for(std::chrono::seconds(1));
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
    this_thread::sleep_for(std::chrono::seconds(1));
}

void Game::handleGameEnd()
{
    this->dial->setText("Koniec gry! ");
    this->tossButton->canToss = false;
    this->menu->showWinners(this->teams, this->playersTotalAmount);
    this->window->close();
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
            this->menu->handleClick(event);
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