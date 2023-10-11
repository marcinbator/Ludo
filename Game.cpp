#include "Game.h"


Game::Game()
{
    this->window = new RenderWindow(VideoMode(900, 900), "Ludo");
    this->centerX = window->getSize().x / 2;
    this->centerY = window->getSize().y / 2;
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
    drawBoard();
    this->window->display();
}

bool Game::isRunning()
{
    return this->window->isOpen();
}

void Game::drawBoard() 
{
    int id = 0;
    tiles[id].setId(id);
    for (int i = 0; i < 5; i++) {
        tiles[id].setPosition(centerX, centerY + tiles[id].getHeight() * i);
        this->window->draw(tiles[id].getSprite());
        id++;
        tiles[id].setId(id);
    }
    for (int i = 1; i <= 4; i++) {
        tiles[id].setPosition(centerX, centerY - tiles[id].getHeight() * i);
        this->window->draw(tiles[id].getSprite());
        id++;
        tiles[id].setId(id);
    }
    for (int i = 1; i <= 4; i++) {
        tiles[id].setPosition(centerX + tiles[id].getWidth() * i, centerY);
        this->window->draw(tiles[id].getSprite());
        id++;
        tiles[id].setId(id);
    }
    for (int i = 1; i <= 4; i++) {
        tiles[id].setPosition(centerX - tiles[id].getWidth() * i, centerY);
        this->window->draw(tiles[id].getSprite());
        id++;
        tiles[id].setId(id);
    }
}
