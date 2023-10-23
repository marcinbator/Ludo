#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Dial
{
	Text text;
	Font font;

	void initText(string text, int x, int y);

public:
	Dial() = delete;
	Dial(string text, int x, int y);

	void draw(RenderWindow* window);
	void setText(string text);
	void setText(string text, Color color);
};

