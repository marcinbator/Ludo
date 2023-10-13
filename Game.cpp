#include "Game.h"

Game::Game()
{
    this->window = new RenderWindow(VideoMode(900, 900), "Ludo");
    this->board = nullptr;
    *this->teams = nullptr;
    *this->pawns = nullptr;
}

void Game::update()
{
    this->pollEvents();
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
            for (int i=0; i<72; i++)
            {
                Tile tile = this->board->getTiles()[i];
                if (tile.isClicked(event)) {
                    tile.handleClick();
                }
            }
            for (int i = 0; i < 16; i++) {
                if (pawns[i]->isClicked(event)) {
                    this->pawns[i]->handleClick();
                }
            }
            
        }
    }
}

void Game::renderPawns() {
    for (int i = 0; i < 4; i++) {
        Pawn* pawn = new Pawn(i, this->teams[0], this->window);
        this->pawns[i] = pawn;
        Tile* tile = this->board->getTileById(101 + i);
        this->pawns[i]->place(tile);
    }
    for (int i = 4; i < 8; i++) {
        Pawn* pawn = new Pawn(i, this->teams[1], this->window);
        this->pawns[i] = pawn;
        Tile* tile = this->board->getTileById(111 + i-4);
        this->pawns[i]->place(tile);
    }
    for (int i = 8; i < 12; i++) {
        Pawn* pawn = new Pawn(i, this->teams[2], this->window);
        this->pawns[i] = pawn;
        Tile* tile = this->board->getTileById(121 + i-8);
        this->pawns[i]->place(tile);
    }
    for (int i = 12; i < 16; i++) {
        Pawn* pawn = new Pawn(i, this->teams[3], this->window);
        this->pawns[i] = pawn;
        Tile* tile = this->board->getTileById(131 + i-12);
        this->pawns[i]->place(tile);
    }
}

void Game::render()
{
    this->window->clear();
    this->board = new Board(this->window);
    this->createTeams();
    this->renderPawns();
    this->window->display();
}

void Game::createTeams()
{
    Team* t1 = new Team(1, "Czerwony", this->board->getTileById(1), "images/Rpawn.png");
    Team* t2 = new Team(2, "Niebieski", this->board->getTileById(11), "images/Bpawn.png");
    Team* t3 = new Team(3, "Zielony", this->board->getTileById(21), "images/Gpawn.png");
    Team* t4 = new Team(4, "Zolty", this->board->getTileById(31), "images/Ypawn.png");
    this->teams[0] = t1;
    this->teams[1] = t2;
    this->teams[2] = t3;
    this->teams[3] = t4;
}

bool Game::isRunning()
{
    return this->window->isOpen();
}

void Game::testMove()
{

}


