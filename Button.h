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

	void initSprite(int x, int y);
	void initText(std::string& text);

public:
	Button() = delete;
	Button(string text, int x, int y);

	bool canToss;

	void handleClick(int& dice);
	int random(int min, int max);
	void draw(RenderWindow* window);

	const bool isClicked(Event event);
};

