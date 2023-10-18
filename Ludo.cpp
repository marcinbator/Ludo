#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Menu.h"

using namespace sf;

int main() {
    Menu menu;
    Game game(menu.getPlayers(), menu.getSi());
    while (game.isRunning()) {
        game.update();
        game.render();
    }
    return 0;
}