#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Tile
{
public:
    Tile();
    void setPosition(float x, float y);
    void rotate(float angle);
    Sprite getSprite() const;
    bool isClicked(Event event) const;
    void handleClick() const;
    int height;
    int width;
    int id;
private:
    Texture texture;
    Sprite sprite;
};