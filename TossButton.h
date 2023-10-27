#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Random.h"
#include "Button.h"
#include "Board.h"

class TossButton : public Button
{
public:
	bool canToss;

	TossButton() = delete;
	TossButton(string text, int x, int y);

	void handleClick(int& dice, Board* board);
private:
	void initText(string text);
};

