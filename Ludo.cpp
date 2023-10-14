#include <SFML/Graphics.hpp>
#include "Game.h"

using namespace sf;

int main() {
    Game game;
    while (game.isRunning()) {
        game.update();
        game.render();
    }
    return 0;
}

int random(int min, int max)
{
    static bool first = true;
    if (first)
    {
        srand(time(NULL));
        first = false;
    }
    return min + rand() % ((max + 1) - min);
}