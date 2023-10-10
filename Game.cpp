#include "Game.h"

Game::Game(RenderWindow& window)
    : window(window)
{
    this->centerX = window.getSize().x / 2;
    this->centerY = window.getSize().y / 2;
}

void Game::run()
{
    window.clear();
    drawBoard();
    window.display();
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
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

}

void Game::drawBoard() 
{
    int id = 0;
    tiles[id].setId(id);
    for (int i = 0; i < 5; i++) {
        tiles[id].setPosition(centerX, centerY + tiles[id].getHeight() * i);
        window.draw(tiles[id].getSprite());
        id++;
        tiles[id].setId(id);
    }
    for (int i = 1; i <= 4; i++) {
        tiles[id].setPosition(centerX, centerY - tiles[id].getHeight() * i);
        window.draw(tiles[id].getSprite());
        id++;
        tiles[id].setId(id);
    }
    for (int i = 1; i <= 4; i++) {
        tiles[id].setPosition(centerX + tiles[id].getWidth() * i, centerY);
        window.draw(tiles[id].getSprite());
        id++;
        tiles[id].setId(id);
    }
    for (int i = 1; i <= 4; i++) {
        tiles[id].setPosition(centerX - tiles[id].getWidth() * i, centerY);
        window.draw(tiles[id].getSprite());
        id++;
        tiles[id].setId(id);
    }
}
