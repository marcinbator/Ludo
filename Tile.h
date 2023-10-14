#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Pawn;

class Tile
{
    int id;
    int height;
    int width;
    Texture texture;
    Sprite sprite;
    Pawn* currentPawn;
public:
    Tile();
    Tile(int x, int y, int rotateDeg, string texturePath);
    void setId(int id);
    int getPositionX();
    int getPositionY();
    int getHeight();
    int getWidth();
    int getId();
    Pawn* getCurrentPawn();
    void setCurrentPawn(Pawn* pawn);
    Sprite getSprite() const;
    bool isClicked(Event event) const;
    void handleClick();
    void drawTile(RenderWindow* window);
};