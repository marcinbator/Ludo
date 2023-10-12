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
    int currentPawnId;
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
    int getCurrentPawnId();
    void setCurrentPawnId(int id);
    Sprite getSprite() const;
    bool isClicked(Event event) const;
    int handleClick() const;
    void drawTile(string texturePath, int x, int y, RenderWindow* window);
    void drawTile(string texturePath, int rotateDeg, int x, int y, RenderWindow* window);
    void drawTile(string texturePath, int x, int y, RenderWindow* window, int& id);
};