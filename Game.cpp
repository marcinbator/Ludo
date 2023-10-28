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
    delete this->initialMenu;
    delete this->leaderBoard;
    delete this->board;
    for (int i = 0; i < this->playersAmount; i++)
        delete this->teams[i];
    for (int i = 0; i < this->playersAmount * this->PAWNS_TEAM; i++)
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
    this->window = new sf::RenderWindow(sf::VideoMode(900, 900), "Ludo", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
    sf::Image icon;
    icon.loadFromFile(string(TEXTURE_PATH) + "logo.png");
    this->window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    this->initSounds();
}

void Game::initSounds()
{
    string soundPath = "music/";
    //music
    this->musicBuffer.loadFromFile(soundPath + "audio.wav");
    this->music.setBuffer(musicBuffer);
    this->music.play();
    this->music.setLoop(true);
    //sounds
    string soundNames[] = { "move.wav", "obstructed.wav", "win.wav" };
    for (int i = 0; i < 3; i++) {
        this->soundsBuffers[i].loadFromFile(soundPath + soundNames[i]);
        this->sounds[i].setBuffer(this->soundsBuffers[i]);
    }
}

void Game::renderPawns() {
    for (int i = 0; i < this->playersAmount*this->PAWNS_TEAM; i++) {
        this->pawns[i]->draw(this->pawns[i]->getCurrentTile(), this->window);
    }
}

void Game::initGame()
{
    this->livePlayersAmount = initialMenu->getPlayersAmount();
    this->aiPlayersAmount = initialMenu->getAiPlayersAmount();
    this->playersAmount = this->livePlayersAmount + this->aiPlayersAmount;

    const string names[] = { "Czerwony", "Niebieski", "Zielony", "Zolty" };
    const int startTiles[] = { 1, 11, 21, 31 };
    const int baseTiles[] = { 101, 111, 121, 131 };

    this->createLivePlayers(names, baseTiles, startTiles);
    this->createAiPlayers(names, baseTiles, startTiles);
    for (int i = 0; i < this->playersAmount; i++) { //assign pawns to teams
        Pawn* subpawns[] = { this->pawns[i * this->PAWNS_TEAM],
            this->pawns[i * this->PAWNS_TEAM + 1],
            this->pawns[i * this->PAWNS_TEAM + 2],
            this->pawns[i * this->PAWNS_TEAM + 3] };
        this->teams[i]->setPawns(subpawns);
    }
    this->orderPlayers(names);
    this->currentTeamId = random(0, playersAmount - 1);
    this->setNextTeamId(this->dice);
    this->delay(this->delayTime, "");
    cout << "Game loaded successfully.\nPlayers: " << this->livePlayersAmount << "+" << this->aiPlayersAmount << endl;
    cout << "Current player: " << this->teams[this->currentTeamId]->getName() << endl;

    //debug
    //for (int i = 0; i < this->PAWNS_TEAM; i++) {
    //    this->pawns[i]->draw(this->board->getTileById(this->PAWNS_TEAM0 - i), this->window);
    //    this->pawns[i]->setIsAtBase(false);
    //}
}

void Game::createLivePlayers(const string* names, const int* baseTiles, const int* startTiles)
{
    const string images[] = { string(TEXTURE_PATH) + "Rpawn.png", string(TEXTURE_PATH) + "Bpawn.png", string(TEXTURE_PATH) + "Gpawn.png", string(TEXTURE_PATH) + "Ypawn.png" };
    int menuPlayersUsed = 0;
    for (int i = 0; i < this->livePlayersAmount; i++) {
        for (int j = menuPlayersUsed; j < this->PAWNS_TEAM; j++) {
            if (this->initialMenu->getPlayersColors()[j] != "") { //player exists
                Team* team = new Team(i, false, names[j], this->board->getTileById(startTiles[j]), images[j], this->initialMenu->getLevel());
                this->teams[i] = team;
                menuPlayersUsed = j + 1;
                for (int k = 0; k < this->PAWNS_TEAM; k++) {
                    int index = i * this->PAWNS_TEAM + k;
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
    const string aiImages[] = { string(TEXTURE_PATH) + "RpawnAI.png", string(TEXTURE_PATH) + "BpawnAI.png", string(TEXTURE_PATH) + "GpawnAI.png", string(TEXTURE_PATH) + "YpawnAI.png" };
    int menuAiPlayersUsed = 0;
    for (int i = this->livePlayersAmount; i < this->playersAmount; i++) {
        for (int j = menuAiPlayersUsed; j < this->PAWNS_TEAM; j++) {
            if (this->initialMenu->getAiPlayersColors()[j] != "") {  //player exists
                Team* team = new Team(i, true, names[j], this->board->getTileById(startTiles[j]), aiImages[j], this->initialMenu->getLevel());
                this->teams[i] = team;
                menuAiPlayersUsed = j + 1;
                for (int k = 0; k < this->PAWNS_TEAM; k++) {
                    int index = i * this->PAWNS_TEAM + k;
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

void Game::orderPlayers(const string* namesOrder)
{
    int index = 0;
    string customOrder[this->MAX_TEAMS];
    for (int i = 0; i < this->MAX_TEAMS; i++) { //set custom order
        bool matches = false;
        for (int j = 0; j < this->playersAmount; j++) {
            if (namesOrder[i] == this->teams[j]->getName()) {
                matches = true;
            }
        }
        if (matches) {
            customOrder[index] = namesOrder[i];
            index++;
        }
    }
    for (int i = 0; i < this->playersAmount; i++) { //swap teams if necessary
        if (this->teams[i]->getName() != customOrder[i]) {
            for (int j = 0; j < this->playersAmount; j++) {
                if (this->teams[j]->getName() == customOrder[i]) {
                    Team* team = this->teams[j];
                    this->teams[j] = this->teams[i];
                    this->teams[i] = team;
                    break;
                }
            }
        }
    }
    for (int i = 0; i < this->playersAmount; i++) {
        this->teams[i]->setId(i);
    }
}

void Game::handleAiMove() {
    this->board->getTossButton()->handleClick(this->dice, this->board);
    this->delay(this->delayTime, "");
    if (!this->teams[this->currentTeamId]->getAi()->move(this->teams[this->currentTeamId], this->dice, this->window, this->board)) { //move not possible
        this->board->getDial()->setText("Gracz zablokowany");
        this->sounds[this->OBSTRUCTED_SOUND_ID].play();
        this->delay(this->delayTime/2, "");
    }
    else {
        this->sounds[this->MOVE_SOUND_ID].play();
    }
    if (this->teams[this->currentTeamId]->isWin()) { //check win
        this->handleSingleWin();
    }
    int diceT = this->dice;
    this->dice = 0;
    this->setNextTeamId(diceT);
    this->delay(this->delayTime/2, "");
}

void Game::handlePlayerTossClick() {
    this->board->getTossButton()->handleClick(this->dice, this->board);
    int autoMove = this->teams[this->currentTeamId]->getIsPossibleMovesOne(this->dice, this->board);
    if (autoMove != -1) { //auto move - one option
        this->handlePawnClick(autoMove);
    }
    this->board->getDial()->setText("Ruch gracza: " + this->teams[this->currentTeamId]->getName());
    this->board->getTossButton()->canToss = false;
    if (this->teams[currentTeamId]->areAllObstructed(this->dice, this->board)) { //player is obstructed
        this->handleAllObstructed();
        return;
    }
}

void Game::handlePawnClick(int pawnId) {
    if (this->pawns[pawnId]->getTeam()->getId() == this->currentTeamId) { //pawn of correct team clicked
        if (this->pawns[pawnId]->handleClick(this->dice, this->window, this->board)) { //if move is possible -> move itself
            this->sounds[this->MOVE_SOUND_ID].play();
            this->board->getTossButton()->canToss = false;
            if (this->teams[this->currentTeamId]->isWin()) { //check win
                this->handleSingleWin();
            }
            int diceT = this->dice;
            this->dice = 0;
            this->setNextTeamId(diceT); //get next or detect game ends
        }
        else {
            this->sounds[this->OBSTRUCTED_SOUND_ID].play();        }
    }
    else {
        this->sounds[this->OBSTRUCTED_SOUND_ID].play();
        this->board->getDial()->setText("Blad! Teraz ruch gracza " + this->teams[this->currentTeamId]->getName());
    }
}

void Game::handleMouseOverPawn(int pawnId)
{
    if (this->pawns[pawnId]->getTeam()->getId() == this->currentTeamId && this->dice != 0) {
        this->pawns[pawnId]->handleMouseOver(this->dice, this->window, this->board);
    }
}

void Game::handleWarpClick()
{
    this->isWarp = !this->isWarp;
    string texture = this->isWarp ? string(TEXTURE_PATH) + "unwarp.png" : string(TEXTURE_PATH) + "warp.png";
    this->delayTime = this->isWarp ? 100 : 800;
    this->board->getWarp()->setTexture(texture);
}

void Game::handleSoundClick()
{
    this->isSound = !this->isSound;
    string texture = this->isSound ? string(TEXTURE_PATH) + "sound.png" : string(TEXTURE_PATH) + "soundOff.png";
    if (this->isSound) {
        this->music.play();
    }
    else {
        this->music.pause();
    }
    this->board->getSound()->setTexture(texture);
}

void Game::setNextTeamId(int diceT)
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
    if (diceT == 6 && this->teams[this->currentTeamId]->getPrime() < 3) { //prime - retoss
        this->teams[this->currentTeamId]->setPrime(this->teams[this->currentTeamId]->getPrime() + 1);
        this->selectPlayer();
        this->board->getDial()->setText("Ponowny rzut gracza " + this->teams[this->currentTeamId]->getName());
        this->delay(this->delayTime, "");
        return;
    }
    else {
        this->teams[this->currentTeamId]->setPrime(0);
    }
    do {
        id = (id + 1) % this->playersAmount;
        attempts++;
    } while (this->teams[id]->isWin() && attempts < this->playersAmount);
    this->currentTeamId = id;
    this->selectPlayer();
    this->board->getDial()->setText("Rzut gracza " + this->teams[this->currentTeamId]->getName());
    this->delay(this->delayTime, "");
}

void Game::selectPlayer()
{
    if (!this->teams[this->currentTeamId]->getIsAi()) { //not ai - let player toss
        this->board->getTossButton()->canToss = true;
    }
    else {
        this->board->getTossButton()->canToss = false;
    }
}

void Game::handleAllObstructed()
{
    this->sounds[this->OBSTRUCTED_SOUND_ID].play();
    this->board->getDial()->setText("Gracz zablokowany");
    this->delay(this->delayTime, "");
    this->setNextTeamId(this->dice);
}

void Game::handleSingleWin()
{
    this->teams[this->currentTeamId]->setStanding(this->currentFreePodiumPlace);
    this->sounds[this->WIN_SOUND_ID].play();
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
    sf::Event event;
    while (this->window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed) //close window
        {
            this->restart = false;
            this->window->close();
        }
        else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) //mouse click
        {
            for (int i = 0; i < 72; i++) //tiles clicks
            {
                Tile* tile = this->board->getTiles()[i];
                if (tile->isClicked(event)) {
                    tile->handleClick();
                }
            }
            for (int i = 0; i < this->playersAmount*this->PAWNS_TEAM; i++) { //pawns clicks
                if (pawns[i]->isClicked(event)) {
                    this->handlePawnClick(i);
                }
            }
            if (this->board->getTossButton()->isClicked(event) && this->board->getTossButton()->canToss) { //toss click
                this->handlePlayerTossClick();
            }
            if (this->board->getWarp()->isClicked(event)) { //warp click
                this->handleWarpClick();
            }
            if (this->board->getSound()->isClicked(event)) { //music click
                this->handleSoundClick();
            }
            if (this->board->getRematch()->isClicked(event)) { //rematch click
                this->restart = true;
                window->close();
            }
        }
        for (int i = 0; i < this->playersAmount * this->PAWNS_TEAM; i++) { //pawns mouseover
            if (pawns[i]->isMouseOver(event)) {
                this->handleMouseOverPawn(i);
            }
            else {
                this->pawns[i]->setIsTargetVisible(false);
            }
        }
        for (int i = 0; i < this->playersAmount * this->PAWNS_TEAM; i++) { //visualise possible moves
            if(!this->pawns[i]->getTeam()->getIsAi())
            this->pawns[i]->setIsPossibleVisible(this->currentTeamId, this->dice, this->window, this->board);
        }
    }
}