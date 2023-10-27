#pragma once
#include "Button.h"
#include "InitialMenu.h"
#include "Dial.h"

class MenuConfirmButton : public Button
{
public:
	MenuConfirmButton(string text, int x, int y);
	bool handleClick(InitialMenu* menu, Dial* dial);
private:
	void initText(string text, int x, int y);
};

