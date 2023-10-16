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
	void initText(std::string& text);

public:
	TossButton() = delete;
	TossButton(string text, int x, int y);

	bool canToss;

	void handleClick(int& dice);
	void draw(RenderWindow* window);
	int random(int min, int max);
	const bool isClicked(Event event);
};

