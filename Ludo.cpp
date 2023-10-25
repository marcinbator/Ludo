#include <SFML/Graphics.hpp>
#include "Game.h"
#include "InitialMenu.h"

using namespace sf;

int main() {
    bool restart = false;
    do{
        Game game;
        while (game.isRunning()) {
            game.update(restart);
            game.render();
        }
    } while (restart == true);
    system("pause");
    return 0;
}