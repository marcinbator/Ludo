#include "Game.h"
#include "Board.h"

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
            for (const auto& tile : tiles)
            {
                if (tile.isClicked(event)) {
                    tile.handleClick();
                }
            }
        }
    }
}

void Game::render()
{
    this->window->clear();
    Board board(this->tiles, this->window);
    this->window->display();
}

bool Game::isRunning()
{
    return this->window->isOpen();
}