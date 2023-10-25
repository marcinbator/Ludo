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

	void initSprite(string texturePath, int x, int y);
	void initText(string text, int x, int y);

public:
	Button() = delete;
	Button(string text, string texturePath, int x, int y);

	void draw(RenderWindow* window);
	void handleClick();

	void setText(Text text);
	void setTexture(string texturePath);
	const Sprite getSprite();
	const Text getText();
	const bool isClicked(Event event);
};
