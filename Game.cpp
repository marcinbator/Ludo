#include "Game.h"

Game::Game()
{
    this->initWindow();
    this->board = new Board(window);
    this->board->drawBoard(window);
    this->createTeams();
    this->dice = 0;
    this->currentTeamId = this->tossButton->random(0, 3);
    this->initControls();
    cout << "Game loaded successfully.\n";
    cout << "Current player: " << this->teams[this->currentTeamId]->getName() << endl;
}

Game::~Game()
{
    delete this->window;
    delete this->board;
    delete this->tossButton;
    delete this->dial;
    delete[] *this->pawns;
    delete[] *this->teams;
}

void Game::update()
{
    this->pollEvents();
}

void Game::render()
{
    this->window->clear();
    this->board->drawBoard(this->window);
    this->dial->draw(this->window);
    this->renderPawns();
    if (this->tossButton->canToss) {
        this->tossButton->draw(this->window);
    }
    this->window->display();
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
    this->dial = new Dial("Witaj w grze!\nZaczyna gracz: " + this->teams[this->currentTeamId]->getName(), this->board->getCenterX(), this->board->getCenterY() + 40 * 7);
}

void Game::renderPawns() {
    for (int i = 0; i < 16; i++) {
        this->pawns[i]->draw(this->pawns[i]->getCurrentTile());
    }
}

void Game::createTeams()
{
    const string colors[] = { "Czerwony", "Niebieski", "Zielony", "Zolty" };
    const string images[] = { "images/Rpawn.png", "images/Bpawn.png", "images/Gpawn.png", "images/Ypawn.png" };
    const int startTiles[] = { 1, 11, 21, 31 };
    const int baseTiles[] = { 101, 111 - 4, 121 - 8, 131 - 12 };

    for (int i = 0; i < 4; i++) {
        Team* team = new Team(i + 1, colors[i], this->board->getTileById(startTiles[i]), images[i]);
        this->teams[i] = team;
    }
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 4; i++) {
            int index = j * 4 + i;
            int teamIndex = j;
            int tileId = 101 + j * 10 + i;
            Tile* tile = this->board->getTileById(tileId);
            Pawn* pawn = new Pawn(index, this->teams[teamIndex], this->window, tile, this->board);
            this->pawns[index] = pawn;
        }
    }
    for (int i = 0; i < 4; i++) {
        Pawn* subpawns[] = { this->pawns[i * 4], this->pawns[i * 4 + 1], this->pawns[i * 4 + 2], this->pawns[i * 4 + 3] };
        this->teams[i]->setPawns(subpawns);
    }
}

void Game::handleTossClick() {
    this->tossButton->handleClick(this->dice);
    this->dial->setText("Kostka: " + to_string(this->dice) + ".\nRuch gracza: " + this->teams[this->currentTeamId]->getName());
    this->tossButton->canToss = false;
    if (this->dice != 1 && this->dice != 6 && this->teams[currentTeamId]->areAllObstructed(this->dice)) {
        this->currentTeamId = getNextTeamId();
        this->tossButton->canToss = true;
        this->dial->setText("Kostka: " + to_string(this->dice) + ".\nRzuca gracz " + this->teams[this->currentTeamId]->getName());
        return;
    }
    cout << "Current player: " << this->teams[this->currentTeamId]->getName()<<endl;
}

void Game::handlePawnClick(int pawnId) {
    if (this->pawns[pawnId]->getTeam()->getId() == 1 + this->currentTeamId) {
        if (this->pawns[pawnId]->handleClick(this->dice, this->tossButton->canToss)) {
            this->currentTeamId = this->getNextTeamId();
            cout << currentTeamId << endl;
            this->dial->setText("Rzut gracza " + this->teams[this->currentTeamId]->getName());
            if (this->teams[this->currentTeamId]->isWin()) {
                this->dial->setText("Zwycieza gracz " + this->teams[this->currentTeamId]->getName() + "!");
                this->tossButton->canToss = false;
            }
        }
    }
    else {
        this->dial->setText("Blad! Teraz ruch gracza " + this->teams[this->currentTeamId]->getName());
    }
}

int Game::getNextTeamId()
{
    int id = 1 + this->currentTeamId;
    if (id > 3) {
        id = 0;
    }
    return id;
}

void Game::pollEvents()
{
    Event event;
    this->window->setFramerateLimit(60);
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
            for (int i = 0; i < 16; i++) {
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