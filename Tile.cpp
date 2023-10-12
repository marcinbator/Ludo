#include "Tile.h"

Tile::Tile() {
    this->id = 0;
    this->texture.loadFromFile("images/tile.png");
    this->sprite.setTexture(this->texture);
    this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);
    this->width = this->sprite.getGlobalBounds().getSize().x;
    this->height = this->sprite.getGlobalBounds().getSize().y;
    this->currentPawnId = 0;
}

void Tile::setPosition(int x, int y) {
    this->sprite.setPosition(x, y);
}

void Tile::setId(int id)
{
    this->id = id;
}

int Tile::getId()
{
    return this->id;
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

int Tile::getCurrentPawnId()
{
    return this->currentPawnId;
}

void Tile::setCurrentPawnId(int id)
{
    this->currentPawnId = id;
}

void Tile::handleClick() const{
    cout << this->id << endl;
}

void Tile::drawTile(string texturePath, int x, int y, RenderWindow* window)
{
    this->texture.loadFromFile(texturePath);
    this->sprite.setTexture(this->texture);
    this->setPosition(x, y);
    this->setId(id);
    window->draw(this->getSprite());
}

void Tile::drawTile(string texturePath,int rotateDeg, int x, int y, RenderWindow* window)
{
    this->texture.loadFromFile(texturePath);
    this->sprite.setTexture(this->texture);
    this->sprite.setRotation(rotateDeg);
    this->setPosition(x, y);
    this->setId(id);
    window->draw(this->getSprite());
}

void Tile::drawTile(string texturePath, int x, int y, RenderWindow* window, int& id) {
    this->texture.loadFromFile(texturePath);
    this->sprite.setTexture(this->texture);
    this->setPosition(x , y);
    this->setId(id);
    id++;
    window->draw(this->getSprite());
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