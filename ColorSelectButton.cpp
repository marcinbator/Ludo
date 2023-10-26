#include "ColorSelectButton.h"
#include "InitialMenu.h"
#include "Dial.h"

void ColorSelectButton::updateTexture(RenderWindow* window)
{
	this->texture.loadFromFile(this->texturePath);
	this->sprite.setTexture(this->texture);
	window->draw(this->sprite);
}

ColorSelectButton::ColorSelectButton(int id, string color, int x, int y) : Button("", "images/tile.png", x, y)
{
	this->id = id;
	this->isSelected = false;
	this->isAvailable = true;
	this->color = color;
	this->texturePath = "images/tile" + this->color + ".png";
	this->texture.loadFromFile(this->texturePath);
	this->sprite.setTexture(this->texture);
	this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);
	this->sprite.setPosition(x, y);
}

void ColorSelectButton::draw(RenderWindow* window)
{
	if (!this->isSelected) { this->texturePath = "images/tile" + this->color + "G.png"; }
	else { this->texturePath = "images/tile" + this->color + ".png"; }
	this->updateTexture(window);
}

void ColorSelectButton::handleClick(InitialMenu* initialMenu, Dial* dial, ColorSelectButton* parallelButton)
{
	if (this->isAvailable) {
		this->isSelected = !this->isSelected;
		parallelButton->isAvailable = !parallelButton->isAvailable;
	}
}

void ColorSelectButton::setIsAvailable(bool isAvailable)
{
	this->isAvailable = isAvailable;
}

string ColorSelectButton::getColor()
{
	return this->color;
}

bool ColorSelectButton::getIsSelected()
{
	return this->isSelected;
}
