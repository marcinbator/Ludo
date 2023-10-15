#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;

class Button
{
	Text text;
	Font font;
	Texture texture;
	Sprite sprite;

	int random(int min, int max);

public:
	Button() = delete;
	Button(string text, int x, int y);

	bool canToss;

	void handleClick(int& dice);
	void draw(RenderWindow* window);

	const bool isClicked(Event event);
	void setCanToss(bool canToss);
	const bool isCanToss();
};

