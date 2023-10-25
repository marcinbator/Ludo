#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Button.h"

class Board;

class TossButton : public Button
{
	void initText(string text);

public:
	TossButton(string text, int x, int y);

	bool canToss;

	void handleClick(int& dice, Board* board);
};

