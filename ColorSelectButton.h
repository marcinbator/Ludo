#pragma once
#include "Button.h"
#include <SFML/Graphics.hpp>
#include "InitialMenu.h"
#include "Dial.h"

using namespace std;

class ColorSelectButton : public Button
{
	int id{};
	bool isSelected;
	bool isAvailable;
	string color;
	string texturePath;
public:
	ColorSelectButton() = delete;
	ColorSelectButton(int id, string texturePath, int x, int y);

	void draw(sf::RenderWindow* window);
	void handleClick(InitialMenu* initialMenu, Dial* dial, ColorSelectButton* parallelButton);
	void setIsAvailable(bool isAvailable);

	string getColor() const;
	bool getIsSelected() const;
private:
	void updateTexture(sf::RenderWindow* window);
};

