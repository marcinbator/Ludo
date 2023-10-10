#include "Tile.h"

Tile::Tile() {
    this->texture.loadFromFile("tile.png");
    this->sprite.setTexture(texture);
    this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);
    this->width=this->sprite.getGlobalBounds().getSize().x;
    this->height=this->sprite.getGlobalBounds().getSize().y;
}

void Tile::setPosition(float x, float y) {
    this->sprite.setPosition(x, y);
}

void Tile::rotate(float angle) {
    this->sprite.rotate(angle);
}

Sprite Tile::getSprite() const
{
    return this->sprite;
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

void Tile::handleClick() const{
    cout << this->id << endl;
}
