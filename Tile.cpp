#include "Tile.h"
#include "Pawn.h"

Tile::Tile()
{
    this->id = 0;
    this->width = 40;
    this->height = 40;
    this->currentPawn = nullptr;
}

Tile::Tile( int x, int y, int rotateDeg, string texturePath) {
    this->id = 0;
    initSprite(texturePath, x, y, rotateDeg);
    this->currentPawn = nullptr;
}

void Tile::drawTile(sf::RenderWindow* window)
{
    window->draw(this->sprite);
}

void Tile::handleClick() {
    cout <<"Tile " << this->id << " clicked.\n";
}

void Tile::setId(int id)
{
    this->id = id;
}

void Tile::setCurrentPawn(Pawn* pawn)
{
    this->currentPawn = pawn;
}

int Tile::getId() const
{
    return this->id;
}

Pawn* Tile::getCurrentPawn()
{
    return this->currentPawn;
}

int Tile::getWidth() const
{
    return this->width;
}

int Tile::getHeight() const
{
    return this->height;
}

int Tile::getPositionX() const
{
    return this->sprite.getPosition().x;
}

int Tile::getPositionY() const
{
    return this->sprite.getPosition().y;
}

sf::Sprite Tile::getSprite() const
{
    return this->sprite;
}

void Tile::initSprite(string texturePath, int x, int y, int rotateDeg)
{
    this->width = this->sprite.getGlobalBounds().getSize().x;
    this->height = this->sprite.getGlobalBounds().getSize().y;
    this->texture.loadFromFile(texturePath);
    this->sprite.setTexture(this->texture);
    this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);
    this->sprite.setPosition(x, y);
    this->sprite.rotate(rotateDeg);
}