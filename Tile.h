#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Tile
{
    int id;
    int height;
    int width;
    Texture texture;
    Sprite sprite;
public:
    Tile();
    void setPosition(int x, int y);
    void setId(int id);
    int getId();
    int getHeight();
    int getWidth();
    int getPositionX();
    int getPositionY();
    Sprite getSprite() const;
    bool isClicked(Event event) const;
    void handleClick() const;
    void drawTile(string texturePath, int x, int y, RenderWindow* window);
    void drawTile(string texturePath, int rotateDeg, int x, int y, RenderWindow* window);
    void drawTile(string texturePath, int x, int y, RenderWindow* window, int& id);
};