#include "Tile.h"
#include "Pawn.h"

Tile::Tile()
{
    this->id = 0;
    this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);
    this->width = 40;
    this->height = 40;
    this->currentPawn = nullptr;
}

Tile::Tile( int x, int y, int rotateDeg, string texturePath) {
    this->id = 0;
    this->texture.loadFromFile(texturePath);
    this->sprite.setTexture(this->texture);
    this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);
    this->sprite.setPosition(x, y);
    this->sprite.rotate(rotateDeg);
    this->width = this->sprite.getGlobalBounds().getSize().x;
    this->height = this->sprite.getGlobalBounds().getSize().y;
    this->currentPawn = nullptr;
}

void Tile::setId(int id)
{
    this->id = id;
}

int Tile::getId()
{
    return this->id;
}

Pawn* Tile::getCurrentPawn()
{
    return this->currentPawn;
}

void Tile::setCurrentPawn(Pawn* pawn)
{
    this->currentPawn = pawn;
}

int Tile::getHeight()
{
    return this->height;
}

int Tile::getWidth()
{
    return this->width;
}

int Tile::getPositionX()
{
    return this->sprite.getPosition().x;
}

Sprite Tile::getSprite() const
{
    return this->sprite;
}

int Tile::getPositionY()
{
    return this->sprite.getPosition().y;
}

bool Tile::isClicked(Event event) const
{
    if (this->getSprite()
        .getGlobalBounds()
        .contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
    {
        return true;
    }
    return false;
}

void Tile::handleClick(){
    cout << this->id <<" "<< endl;
}

void Tile::drawTile( RenderWindow* window)
{
    window->draw(this->sprite);
}

Tile* getTileById(int id, Tile* tiles)
{
    for (int i = 0; i < 16; i++) {
        if (tiles[i].getId() == id) {
            return &tiles[i];
        }
    }
    return nullptr;
}