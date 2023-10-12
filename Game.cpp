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
    this->window->setFramerateLimit(60);
    while (this->window->pollEvent(event))
    {
        if (event.type == Event::Closed)
        {
            this->window->close();
        }
        else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
        {
            for (int i=0; i<73; i++)
            {
                Tile tile = this->board->getTiles()[i];
                if (tile.isClicked(event)) {
                    tile.handleClick();
                    break;
                }
            }
            
        }
    }
}

void Game::renderPawns() {
    Pawn pawns[] = {
        Pawn(1, TeamName(red), this->window),
        Pawn(2, TeamName(red), this->window),
        Pawn(3, TeamName(red), this->window),
        Pawn(4, TeamName(red), this->window),
        Pawn(5, TeamName(blue), this->window),
        Pawn(6, TeamName(blue), this->window),
        Pawn(7, TeamName(blue), this->window),
        Pawn(8, TeamName(blue), this->window),
        Pawn(9, TeamName(green), this->window),
        Pawn(10, TeamName(green), this->window),
        Pawn(11, TeamName(green), this->window),
        Pawn(12, TeamName(green), this->window),
        Pawn(13, TeamName(yellow), this->window),
        Pawn(14, TeamName(yellow), this->window),
        Pawn(15, TeamName(yellow), this->window),
        Pawn(16, TeamName(yellow), this->window)
    };
    for (int i = 0; i < 4; i++) {
        Tile* tile = this->board->getTileById(101+i);
        pawns[i].draw(tile);
    }
    for (int i = 4; i < 8; i++) {
        Tile* tile = this->board->getTileById(111 + i-4);
        pawns[i].draw(tile);
    }
    for (int i = 8; i < 12; i++) {
        Tile* tile = this->board->getTileById(121 + i-8);
        pawns[i].draw(tile);
    }
    for (int i = 12; i < 16; i++) {
        Tile* tile = this->board->getTileById(131 + i-12);
        pawns[i].draw(tile);
    }
    this->pawns = pawns;
}

void Game::render()
{
    this->window->clear();
    this->board = new Board(this->window);
    renderPawns();
    this->window->display();
}

void Game::create()
{
    Player players[] = {
        Player(1, "Czerwony", this->pawns, this->board->getTileById(1)),
        Player(2, "Niebieski", this->pawns, this->board->getTileById(1)),
        Player(3, "Zielony", this->pawns, this->board->getTileById(1)),
        Player(4, "Zolty", this->pawns, this->board->getTileById(1))
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


