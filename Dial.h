#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"

using namespace std;

class Dial
{
	sf::Text text;
	sf::Font font;
public:
	Dial() = delete;
	Dial(string text, int x, int y);

	void draw(sf::RenderWindow* window);
	void setText(string text);
	void setText(string text, sf::Color color);
private:
	void initText(string text, int x, int y);
};

