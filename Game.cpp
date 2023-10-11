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
    //up
    for (int i = 1; i < 5; i++) {
        for (int j = -1; j <= 1; j+=2) {
            tiles[id].drawTile("images/tile.png", centerX + j * tiles[id].getWidth(), centerY + tiles[id].getHeight() * i, this->window, id);
        }
        tiles[id].drawTile("images/tileRed.png", centerX, centerY + tiles[id].getHeight() * i, this->window, id);
    }
    for (int i = -1; i <= 1; i++) {
        tiles[id].drawTile("images/tile.png", centerX + i * tiles[id].getWidth(), centerY + tiles[id].getHeight() * 5, this->window, id);
    }
    //down
    for (int i = 1; i <= 4; i++) {
        for (int j = -1; j <= 1; j += 2) {
            tiles[id].drawTile("images/tile.png", centerX + j * tiles[id].getWidth(), centerY - tiles[id].getHeight() * i, this->window, id);
        }
        tiles[id].drawTile("images/tileGreen.png", centerX, centerY - tiles[id].getHeight() * i, this->window, id);
    }
    for (int i = -1; i <= 1; i++) {
        tiles[id].drawTile("images/tile.png", centerX + i * tiles[id].getWidth(), centerY - tiles[id].getHeight() * 5, this->window, id);
    }
    //left
    tiles[id].drawTile("images/tileBlue.png", centerX - tiles[id].getWidth(), centerY, this->window, id);
    for (int i = 2; i <= 4; i++) {
        for (int j = -1; j <= 1; j += 2) {
            tiles[id].drawTile("images/tile.png", centerX - tiles[id].getWidth() * i, centerY + j * tiles[id].getHeight(), this->window, id);
        }
        tiles[id].drawTile("images/tileBlue.png", centerX - tiles[id].getWidth() * i, centerY, this->window, id);
    }
    for (int i = -1; i <= 1; i++) {
        tiles[id].drawTile("images/tile.png", centerX - tiles[id].getWidth() * 5, centerY - i * tiles[id].getHeight(), this->window, id);
    }
    //right
    tiles[id].drawTile("images/tileYellow.png", centerX + tiles[id].getWidth(), centerY, this->window, id);
    for (int i = 2; i <= 4; i++) {
        for (int j = -1; j <= 1; j += 2) {
            tiles[id].drawTile("images/tile.png", centerX + tiles[id].getWidth() * i, centerY + j * tiles[id].getHeight(), this->window, id);
        }
        tiles[id].drawTile("images/tileYellow.png", centerX + tiles[id].getWidth() * i, centerY, this->window, id);
    }
    for (int i = -1; i <= 1; i++) {
        tiles[id].drawTile("images/tile.png", centerX + tiles[id].getWidth() * 5, centerY - i * tiles[id].getHeight(), this->window, id);
    }
    tiles[12].drawTile("images/arrow.png", tiles[12].getPositionX(), tiles[12].getPositionY(), this->window);
    tiles[42].drawTile("images/arrow.png", 90, tiles[42].getPositionX(), tiles[42].getPositionY(), this->window);
    tiles[29].drawTile("images/arrow.png", 180, tiles[29].getPositionX(), tiles[29].getPositionY(), this->window);
    tiles[53].drawTile("images/arrow.png", 270, tiles[53].getPositionX(), tiles[53].getPositionY(), this->window);
}
