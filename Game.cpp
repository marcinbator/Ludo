#include "Game.h"

Game::Game()
{
    this->window = new RenderWindow(VideoMode(900, 900), "Ludo");
    this->board = nullptr;
    this->players = nullptr;
    *this->pawns = nullptr;
}

void Game::update()
{
    this->pollEvents();
    this->createTeams();
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
        Pawn* pawn = new Pawn(i, TeamName(red), this->window);
        this->pawns[i] = pawn;
        Tile* tile = this->board->getTileById(101 + i);
        this->pawns[i]->draw(tile);
    }
    for (int i = 4; i < 8; i++) {
        Pawn* pawn = new Pawn(i, TeamName(blue), this->window);
        this->pawns[i] = pawn;
        Tile* tile = this->board->getTileById(111 + i-4);
        this->pawns[i]->draw(tile);
    }
    for (int i = 8; i < 12; i++) {
        Pawn* pawn = new Pawn(i, TeamName(green), this->window);
        this->pawns[i] = pawn;
        Tile* tile = this->board->getTileById(121 + i-8);
        this->pawns[i]->draw(tile);
    }
    for (int i = 12; i < 16; i++) {
        Pawn* pawn = new Pawn(i, TeamName(yellow), this->window);
        this->pawns[i] = pawn;
        Tile* tile = this->board->getTileById(131 + i-12);
        this->pawns[i]->draw(tile);
    }
}

void Game::render()
{
    this->window->clear();
    this->board = new Board(this->window);
    this->renderPawns();
    this->window->display();
}

void Game::createTeams()
{
    Player players[] = {
        Player(1, "Czerwony", this->pawns, this->board->getTileById(1)),
        Player(2, "Niebieski", this->pawns, this->board->getTileById(11)),
        Player(3, "Zielony", this->pawns, this->board->getTileById(21)),
        Player(4, "Zolty", this->pawns, this->board->getTileById(31))
    };
    this->players = players;
}

bool Game::isRunning()
{
    return this->window->isOpen();
}

void Game::testMove()
{

}


