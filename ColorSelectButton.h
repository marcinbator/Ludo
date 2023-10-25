#pragma once
#include "Button.h"

class Menu;
class Dial;

class ColorSelectButton : public Button
{
	int id;
	bool isSelected;
	bool isAvailable;
	string color;
	string texturePath;

	void updateTexture(RenderWindow* window);
public:
	ColorSelectButton(int id, string texturePath, int x, int y);

	void draw(RenderWindow* window);
	void handleClick(Menu* menu, Dial* dial, ColorSelectButton* parallelButton);

	void setIsAvailable(bool isAvailable);
	string getColor();
	bool getIsSelected();
};
