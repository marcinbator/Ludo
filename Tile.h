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

    void setPosition(float x, float y);
    void setId(int id);
    int getId();
    int getHeight();
    int getWidth();
    Sprite getSprite() const;
    bool isClicked(Event event) const;

    void handleClick() const;
};