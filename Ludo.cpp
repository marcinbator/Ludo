#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Menu.h"

using namespace sf;

int main() {
    Game game;
    while (game.isRunning()) {
        game.update();
        game.render();
    }
    system("pause");
    return 0;
}