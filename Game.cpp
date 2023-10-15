#include "Game.h"

Game::Game()
{
    this->window = new RenderWindow(VideoMode(900, 900), "Ludo");
    this->board = new Board(window);
    this->board->drawBoard(window);
    this->button = new Button("RZUT", this->board->getCenterX(), this->board->getCenterY() + 40 * 9);
    this->dial = new Dial("Witaj w grze!", this->board->getCenterX(), this->board->getCenterY() + 40 * 7);
    this->createTeams();
    this->dice = 0;
}

Game::~Game()
{
    delete this->window;
    delete this->board;
    delete this->button;
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
    if (this->button->canToss) {
        this->button->draw(this->window);
    }
    this->dial->draw(this->window);
    this->renderPawns();
    this->window->display();
}

bool Game::isRunning()
{
    return this->window->isOpen();
}

//private

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
                    this->pawns[i]->handleClick(this->dice, this->button->canToss);
                }
            }
            if (this->button->isClicked(event) && this->button->canToss) {
                this->button->handleClick(this->dice);
                string text = to_string(this->dice);
                this->dial->setText("Kostka: " + text);
                this->button->canToss = false;
            }
        }
    }
}