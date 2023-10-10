#include "Game.h"
#include <iostream>

using namespace sf;

Game::Game(RenderWindow& window)
    : window(window)
{
    this->centerX = window.getSize().x / 2;
    this->centerY = window.getSize().y / 2;
}

void Game::run()
{
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                for (const auto& tile : tiles)
                {
                    if (tile.isClicked(event)) {
                        tile.handleClick();
                    }
                }
            }
        }
        window.clear();
        drawBoard();
        window.display();
    }
}

void Game::drawBoard() 
{
    int id = 0;
    tiles[id].id = id;
    for (int i = 0; i < 5; i++) {
        tiles[id].setPosition(centerX, centerY + tiles[id].height * i);
        window.draw(tiles[id].getSprite());
        id++;
        tiles[id].id = id;
    }
    for (int i = 1; i <= 4; i++) {
        tiles[id].setPosition(centerX, centerY - tiles[id].height * i);
        window.draw(tiles[id].getSprite());
        id++;
        tiles[id].id = id;
    }
    for (int i = 1; i <= 4; i++) {
        tiles[id].setPosition(centerX + tiles[id].width * i, centerY);
        window.draw(tiles[id].getSprite());
        id++;
        tiles[id].id = id;
    }
    for (int i = 1; i <= 4; i++) {
        tiles[id].setPosition(centerX - tiles[id].width * i, centerY);
        window.draw(tiles[id].getSprite());
        id++;
        tiles[id].id = id;
    }
}
