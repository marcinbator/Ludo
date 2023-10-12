#include <SFML/Graphics.hpp>
#include "Game.h"

using namespace sf;

int main() {
    Game game;
    game.render();
    while (game.isRunning()) {
        game.update();
        
    }
    return 0;
}
