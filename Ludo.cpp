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