#include "Pawn.h"

Pawn::Pawn(int id, TeamName teamName, RenderWindow* window)
{
	this->id = id;
	this->currentTile = nullptr;
	this->isAtBase = true;
	this->isAtTarget = false;
	string texturePath = "images/";
	switch (teamName) {
	case red:
		texturePath += "Rpawn";
		break;
	case blue:
		texturePath += "Bpawn";
		break;
	case green:
		texturePath += "Gpawn";
		break;
	case yellow:
		texturePath += "Ypawn";
	}
	this->texture.loadFromFile(texturePath+".png");
	this->sprite.setTexture(this->texture);
	this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);
	this->window = window;
}

bool Pawn::draw(Tile* tile)
{
	this->sprite.setPosition(tile->getPositionX(), tile->getPositionY());
	this->window->draw(this->sprite);
	this->currentTile = tile;
	this->currentTile->setCurrentPawnId(this->id);
	return true;
}

bool Pawn::isClicked(Event event) 
{
	if (this->sprite
		.getGlobalBounds()
		.contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
	{
		return true;
	}
	return false;
}

void Pawn::handleClick()
{
	cout << "Pawn: " << this->id << endl;
}

void Pawn::move(int tiles)
{
	
}

void Pawn::deploy()
{
	
}

void Pawn::setInBase()
{

}

int Pawn::getId()
{
	return this->id;
}

Tile* Pawn::getCurrentTile()
{
	return this->currentTile;
}

