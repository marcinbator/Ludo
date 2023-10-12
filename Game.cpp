#include "Game.h"

Game::Game()
{
    this->window = new RenderWindow(VideoMode(900, 900), "Ludo");
}

void Game::update()
{
    pollEvents();
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
                if (board->getTiles()[i].isClicked(event)) {
                    board->getTiles()[i].handleClick();
                }
            }
        }
    }
}

void Game::render()
{
    this->window->clear();
    this->board = new Board(this->window);
    this->window->display();
}

bool Game::isRunning()
{
    return this->window->isOpen();
}


