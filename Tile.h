#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;
class Pawn;

class Tile
{
    int id;
    int width;
    int height;
    Texture texture;
    Sprite sprite;
    Pawn* currentPawn;

public:
    Tile();
    Tile(int x, int y, int rotateDeg, string texturePath);

    void drawTile(RenderWindow* window);
    void handleClick();

    void setId(int id);
    void setCurrentPawn(Pawn* pawn);

    int getId();
    int getWidth();
    int getHeight();
    int getPositionX();
    int getPositionY();
    Pawn* getCurrentPawn();
    Sprite getSprite() const;
    bool isClicked(Event event) const;
};