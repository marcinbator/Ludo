#pragma once
#include "Button.h"
class Menu;
class Dial;

class MenuConfirmButton : public Button
{
	void initText(string text, int x, int y);
public:
	MenuConfirmButton(string text, int x, int y);
	bool handleClick(Menu* menu, Dial* dial);
};

