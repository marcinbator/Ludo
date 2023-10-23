#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;

class Button
{
protected:
	Font font;
	Text text;
	Texture texture;
	Sprite sprite;

	void initSprite(int x, int y);
	void initText(string text, int x, int y);

public:
	Button() = delete;
	Button(string text, int x, int y);

	void draw(RenderWindow* window);
	void handleClick();

	const Sprite getSprite();
	const bool isClicked(Event event);
};
