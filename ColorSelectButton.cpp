#include "ColorSelectButton.h"

void ColorSelectButton::updateTexture(sf::RenderWindow* window)
{
	this->texture.loadFromFile(this->texturePath);
	this->sprite.setTexture(this->texture);
	window->draw(this->sprite);
}

ColorSelectButton::ColorSelectButton(int id, string color, int x, int y) : Button("", string(TEXTURE_PATH) + "tile.png", x, y)
{
	this->id = id;
	this->isSelected = false;
	this->isAvailable = true;
	this->color = color;
	this->texturePath = string(TEXTURE_PATH) + "tile" + this->color + ".png";
	this->texture.loadFromFile(this->texturePath);
	this->sprite.setTexture(this->texture);
	this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);
	this->sprite.setPosition(x, y);
	
}

void ColorSelectButton::draw(sf::RenderWindow* window)
{
	if (!this->isSelected) { this->texturePath = string(TEXTURE_PATH) + "tile" + this->color + "G.png"; }
	else { this->texturePath = string(TEXTURE_PATH) + "tile" + this->color + ".png"; }
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

string ColorSelectButton::getColor() const
{
	return this->color;
}

bool ColorSelectButton::getIsSelected() const
{
	return this->isSelected;
}
