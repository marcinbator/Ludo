#include "Game.h"

Game::Game()
{
    this->window = new RenderWindow(VideoMode(900, 900), "Ludo");
}

void Game::update()
{
    this->pollEvents();
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
            for (int i=0; i<100; i++)
            {
                Tile tile = this->board->getTiles()[i];
                if (tile.isClicked(event)) {
                    tile.handleClick();
                }
            }
        }
    }
}

void Game::renderPawns() {
    Tile* tile = this->board->getTileById(102);
    Pawn pawn(1, TeamName(red), this->window);
    pawn.draw(tile);
}

void Game::render()
{
    this->window->clear();
    this->board = new Board(this->window);
    renderPawns();
    this->window->display();
}

bool Game::isRunning()
{
    return this->window->isOpen();
}


