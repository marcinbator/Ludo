#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;

class TossButton
{
	Text text;
	Font font;
	Texture texture;
	Sprite sprite;

	void initSprite(int x, int y);
	void initText(string text);

public:
	TossButton() = delete;
	TossButton(string text, int x, int y);

	bool canToss;

	void draw(RenderWindow* window);
	void handleClick(int& dice);

	const bool isClicked(Event event);
};

