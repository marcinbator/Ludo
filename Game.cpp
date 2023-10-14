#include "Game.h"

Game::Game()
{
    this->window = new RenderWindow(VideoMode(900, 900), "Ludo");
    this->board = new Board(this->window);
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
               Tile* tile = this->board->getTiles()[i];
                if (tile->isClicked(event)) {
                    tile->handleClick();
                }
            }
            
        }
    }
}


void Game::render()
{
    this->window->clear();
    this->board->drawBoard(this->window);
    this->window->display();
}

bool Game::isRunning()
{
    return this->window->isOpen();
}
