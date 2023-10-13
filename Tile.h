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
    Pawn* currentPawn;
    Texture texture;
    Sprite sprite;
public:
    Tile();
    void setPosition(int x, int y);
    void setId(int id);
    int getId();
    int getPositionX();
    int getPositionY();
    int getHeight();
    int getWidth();
    void setCurrentPawn(Pawn* pawn);
    Pawn* getCurrentPawn();
    Sprite getSprite() const;
    bool isClicked(Event event) const;
    void handleClick() const;
    void drawTile(string texturePath, int x, int y, RenderWindow* window);
    void drawTile(string texturePath, int rotateDeg, int x, int y, RenderWindow* window);
    void drawTile(string texturePath, int x, int y, RenderWindow* window, int& id);
};