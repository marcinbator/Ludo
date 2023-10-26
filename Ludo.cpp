#include <SFML/Graphics.hpp>
#include "Game.h"

int main() {
    bool restart = false;
    do{
        Game game(restart);
        while (game.isRunning()) {
            game.update();
            game.render();
        }
    } while (restart == true);
    system("pause");
    return 0;
}