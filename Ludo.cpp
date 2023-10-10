#include <SFML/Graphics.hpp>
#include "Game.h"

using namespace sf;

int main() {
    RenderWindow window(VideoMode(900, 900), "Ludo!");
    Game game(window);
    game.run();
    return 0;
}
