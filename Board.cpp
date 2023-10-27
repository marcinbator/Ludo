#include "Board.h"
#include "Dial.h"
#include "TossButton.h"
#include "Button.h"
#include "Tile.h"

Board::Board(sf::RenderWindow* window)
{
    this->setCenter(window);
    this->initTiles();
    this->initButtons();
    this->initBoard();
}

Board::~Board()
{
    delete this->tossButton;
    delete this->dial;
    for (int i = 0; i < TILES_AMOUNT; i++) {
        delete this->tiles[i];
    }
}

void Board::drawBoard(sf::RenderWindow* window) {
    this->initBackground();
    window->draw(this->background);
    window->draw(this->dice);
    this->drawLogo(window);
    this->warp->draw(window);
    this->rematch->draw(window);
    this->dial->draw(window);
    for (int i = 0; i < TILES_AMOUNT; i++) {
        this->tiles[i]->drawTile(window);
    }
}

void Board::setDiceTexture(string texturePath)
{
    this->diceTexture.loadFromFile(texturePath);
    this->dice.setTexture(this->diceTexture);
}

int Board::getCenterX() const
{
    return this->centerX;
}

int Board::getCenterY() const
{
    return this->centerY;
}

Tile* Board::getTileById(int counter) const
{
    for (int i = 0; i < TILES_AMOUNT; i++) {
        if (this->tiles[i]->getId() == counter) {
            return this->tiles[i];
        }
    }
    return nullptr;
}

Button* Board::getWarp() const
{
    return this->warp;
}

Button* Board::getRematch() const
{
    return this->rematch;
}

Dial* Board::getDial() const
{
    return this->dial;
}

TossButton* Board::getTossButton() const
{
    return this->tossButton;
}

Tile** Board::getTiles()
{
    return this->tiles;
}

void Board::setCenter(sf::RenderWindow* window)
{
    this->centerX = window->getSize().x / 2;
    this->centerY = window->getSize().y / 2;
}

void Board::initBackground()
{
    this->bgTexture.loadFromFile(string(TEXTURE_PATH) + "bg.png");
    this->background.setTexture(this->bgTexture);
    this->background.setOrigin(this->background.getGlobalBounds().width / 2, this->background.getGlobalBounds().height / 2);
    this->background.setPosition(this->centerX, this->centerY);
}

void Board::initTiles()
{
    for (int i = 0; i < TILES_AMOUNT; i++) {
        this->tiles[i] = new Tile();
    }
}

void Board::initButtons()
{
    this->tossButton = new TossButton("RZUT", this->getCenterX(), this->getCenterY() + 40 * 9);
    this->dial = new Dial("Witaj w grze!", this->getCenterX(), this->getCenterY() + 40 * 7);
    this->diceTexture.loadFromFile(string(TEXTURE_PATH) + "0dice.png");
    this->dice.setTexture(this->diceTexture);
    this->dice.setOrigin(this->dice.getGlobalBounds().width / 2, this->dice.getGlobalBounds().height / 2);
    this->dice.setPosition(this->centerX + 40 * 9, this->centerY);
    this->dice.setScale(2, 2);
    this->warp = new Button("", string(TEXTURE_PATH) + "warp.png", this->centerX + 40 * 9, this->centerY - 40 * 9);
    this->rematch = new Button("", string(TEXTURE_PATH) + "rematch.png", this->centerX - 40 * 9, this->centerY - 40 * 9);
}

void Board::drawLogo(sf::RenderWindow* window)
{
    sf::Texture texture;
    texture.loadFromFile(string(TEXTURE_PATH) + "logo.png");
    sf::Sprite sprite(texture);
    sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
    sprite.setPosition(this->centerX, this->centerY - 40 * 9);
    sprite.setScale(0.3, 0.3);
    window->draw(sprite);
}

void Board::initBoard()
{
    int counter = 0;
    //bottom
    for (int i = 1; i < 5; i++) {
        for (int j = -1; j <= 1; j += 2) {
            int x = this->centerX + j * this->tiles[counter]->getWidth();
            int y = this->centerY + this->tiles[counter]->getHeight() * i;
            this->tiles[counter] = new Tile( x, y, 0, string(TEXTURE_PATH) + "tile.png");counter++;
        }
        this->tiles[counter] = new Tile( this->centerX,this->centerY + this->tiles[counter]->getHeight() * i, 0, string(TEXTURE_PATH) + "tileRed.png");counter++;
    }
    for (int i = -1; i <= 1; i++) {
        this->tiles[counter] = new Tile( this->centerX + i * this->tiles[counter]->getWidth(),this->centerY + this->tiles[counter]->getHeight() * 5, 0, string(TEXTURE_PATH) + "tile.png");counter++;
    }
    //top
    for (int i = 1; i <= 4; i++) {
        for (int j = -1; j <= 1; j += 2) {
            this->tiles[counter] = new Tile( this->centerX + j * this->tiles[counter]->getWidth(),this->centerY - this->tiles[counter]->getHeight() * i, 0, string(TEXTURE_PATH) + "tile.png");counter++;
        }
        this->tiles[counter] = new Tile( this->centerX,this->centerY - this->tiles[counter]->getHeight() * i, 0, string(TEXTURE_PATH) + "tileGreen.png");counter++;
    }
    for (int i = -1; i <= 1; i++) {
        this->tiles[counter] = new Tile( this->centerX + i * this->tiles[counter]->getWidth(),this->centerY - this->tiles[counter]->getHeight() * 5, 0, string(TEXTURE_PATH) + "tile.png");counter++;
    }
    //left
    this->tiles[counter] = new Tile( this->centerX - this->tiles[counter]->getWidth(),this->centerY, 0, string(TEXTURE_PATH) + "tileBlue.png");counter++;
    for (int i = 2; i <= 4; i++) {
        for (int j = -1; j <= 1; j += 2) {
            this->tiles[counter] = new Tile( this->centerX - this->tiles[counter]->getWidth() * i,this->centerY + j * this->tiles[counter]->getHeight(), 0, string(TEXTURE_PATH) + "tile.png");counter++;
        }
        this->tiles[counter] = new Tile( this->centerX - this->tiles[counter]->getWidth() * i,this->centerY, 0, string(TEXTURE_PATH) + "tileBlue.png");counter++;
    }
    for (int i = -1; i <= 1; i++) {
        this->tiles[counter] = new Tile( this->centerX - this->tiles[counter]->getWidth() * 5,this->centerY - i * this->tiles[counter]->getHeight(), 0, string(TEXTURE_PATH) + "tile.png");counter++; 
    }
    //right
    this->tiles[counter] = new Tile( this->centerX + this->tiles[counter]->getWidth(),this->centerY, 0, string(TEXTURE_PATH) + "tileYellow.png");counter++;
    for (int i = 2; i <= 4; i++) {
        for (int j = -1; j <= 1; j += 2) {
            this->tiles[counter] = new Tile( this->centerX + this->tiles[counter]->getWidth() * i,this->centerY + j * this->tiles[counter]->getHeight(), 0, string(TEXTURE_PATH) + "tile.png");counter++;    
        }
        this->tiles[counter] = new Tile( this->centerX + this->tiles[counter]->getWidth() * i,this->centerY, 0, string(TEXTURE_PATH) + "tileYellow.png");counter++; 
    }
    for (int i = -1; i <= 1; i++) {
        this->tiles[counter] = new Tile( this->centerX + this->tiles[counter]->getWidth() * 5,this->centerY - i * this->tiles[counter]->getHeight(), 0, string(TEXTURE_PATH) + "tile.png");counter++; 
    }
    //arrows
    this->tiles[12] = new Tile(this->tiles[12]->getPositionX(), this->tiles[12]->getPositionY(), 0 ,string(TEXTURE_PATH) + "Rarrow.png");
    this->tiles[42] = new Tile(this->tiles[42]->getPositionX(), this->tiles[42]->getPositionY(), 90 ,string(TEXTURE_PATH) + "Barrow.png");
    this->tiles[29] = new Tile(this->tiles[29]->getPositionX(), this->tiles[29]->getPositionY(), 180 ,string(TEXTURE_PATH) + "Garrow.png");
    this->tiles[53] = new Tile(this->tiles[53]->getPositionX(), this->tiles[53]->getPositionY(), 270 ,string(TEXTURE_PATH) + "Yarrow.png");
    //bases
    //lefttop
    this->tiles[counter] = new Tile( this->centerX - this->tiles[counter]->getWidth() * 5,this->centerY - this->tiles[counter]->getHeight() * 5, 0, string(TEXTURE_PATH) + "tileBlue.png");counter++;
    this->tiles[counter] = new Tile( this->centerX - this->tiles[counter]->getWidth() * 4,this->centerY - this->tiles[counter]->getHeight() * 5, 0, string(TEXTURE_PATH) + "tileBlue.png");counter++;
    this->tiles[counter] = new Tile( this->centerX - this->tiles[counter]->getWidth() * 4,this->centerY - this->tiles[counter]->getHeight() * 4, 0, string(TEXTURE_PATH) + "tileBlue.png");counter++;
    this->tiles[counter] = new Tile( this->centerX - this->tiles[counter]->getWidth() * 5,this->centerY - this->tiles[counter]->getHeight() * 4, 0, string(TEXTURE_PATH) + "tileBlue.png");counter++;
    //righttop
    this->tiles[counter] = new Tile( this->centerX + this->tiles[counter]->getWidth() * 5,this->centerY - this->tiles[counter]->getHeight() * 5, 0, string(TEXTURE_PATH) + "tileGreen.png");counter++;
    this->tiles[counter] = new Tile( this->centerX + this->tiles[counter]->getWidth() * 4,this->centerY - this->tiles[counter]->getHeight() * 5, 0, string(TEXTURE_PATH) + "tileGreen.png");counter++;
    this->tiles[counter] = new Tile( this->centerX + this->tiles[counter]->getWidth() * 4,this->centerY - this->tiles[counter]->getHeight() * 4, 0, string(TEXTURE_PATH) + "tileGreen.png");counter++;
    this->tiles[counter] = new Tile( this->centerX + this->tiles[counter]->getWidth() * 5,this->centerY - this->tiles[counter]->getHeight() * 4, 0, string(TEXTURE_PATH) + "tileGreen.png");counter++;
    //rightbottom
    this->tiles[counter] = new Tile( this->centerX + this->tiles[counter]->getWidth() * 5,this->centerY + this->tiles[counter]->getHeight() * 5, 0, string(TEXTURE_PATH) + "tileYellow.png");counter++;
    this->tiles[counter] = new Tile( this->centerX + this->tiles[counter]->getWidth() * 4,this->centerY + this->tiles[counter]->getHeight() * 5, 0, string(TEXTURE_PATH) + "tileYellow.png");counter++;
    this->tiles[counter] = new Tile( this->centerX + this->tiles[counter]->getWidth() * 4,this->centerY + this->tiles[counter]->getHeight() * 4, 0, string(TEXTURE_PATH) + "tileYellow.png");counter++;
    this->tiles[counter] = new Tile( this->centerX + this->tiles[counter]->getWidth() * 5,this->centerY + this->tiles[counter]->getHeight() * 4, 0, string(TEXTURE_PATH) + "tileYellow.png");counter++;
    //leftbottom
    this->tiles[counter] = new Tile( this->centerX - this->tiles[counter]->getWidth() * 5,this->centerY + this->tiles[counter]->getHeight() * 5, 0, string(TEXTURE_PATH) + "tileRed.png");counter++;
    this->tiles[counter] = new Tile( this->centerX - this->tiles[counter]->getWidth() * 4,this->centerY + this->tiles[counter]->getHeight() * 5, 0, string(TEXTURE_PATH) + "tileRed.png");counter++;
    this->tiles[counter] = new Tile( this->centerX - this->tiles[counter]->getWidth() * 4,this->centerY + this->tiles[counter]->getHeight() * 4, 0, string(TEXTURE_PATH) + "tileRed.png");counter++;
    this->tiles[counter] = new Tile( this->centerX - this->tiles[counter]->getWidth() * 5,this->centerY + this->tiles[counter]->getHeight() * 4, 0, string(TEXTURE_PATH) + "tileRed.png");counter++;
    this->setIds();
}

void Board::setIds() {
    //main route
    this->tiles[12]->setId(1);
    this->tiles[9]->setId(2);
    this->tiles[6]->setId(3);
    this->tiles[3]->setId(4);
    this->tiles[0]->setId(5);
    this->tiles[32]->setId(6);
    this->tiles[35]->setId(7);
    this->tiles[38]->setId(8);
    this->tiles[40]->setId(9);
    this->tiles[41]->setId(10);
    this->tiles[42]->setId(11);
    this->tiles[37]->setId(12);
    this->tiles[34]->setId(13);
    this->tiles[31]->setId(14);
    this->tiles[15]->setId(15);
    this->tiles[18]->setId(16);
    this->tiles[21]->setId(17);
    this->tiles[24]->setId(18);
    this->tiles[27]->setId(19);
    this->tiles[28]->setId(20);
    this->tiles[29]->setId(21);
    this->tiles[25]->setId(22);
    this->tiles[22]->setId(23);
    this->tiles[19]->setId(24);
    this->tiles[16]->setId(25);
    this->tiles[44]->setId(26);
    this->tiles[47]->setId(27);
    this->tiles[50]->setId(28);
    this->tiles[55]->setId(29);
    this->tiles[54]->setId(30);
    this->tiles[53]->setId(31);
    this->tiles[51]->setId(32);
    this->tiles[48]->setId(33);
    this->tiles[45]->setId(34);
    this->tiles[1]->setId(35);
    this->tiles[4]->setId(36);
    this->tiles[7]->setId(37);
    this->tiles[10]->setId(38);
    this->tiles[14]->setId(39);
    this->tiles[13]->setId(40);
    //targets
    this->tiles[11]->setId(51);
    this->tiles[8]->setId(52);
    this->tiles[5]->setId(53);
    this->tiles[2]->setId(54);
    this->tiles[39]->setId(61);
    this->tiles[36]->setId(62);
    this->tiles[33]->setId(63);
    this->tiles[30]->setId(64);
    this->tiles[26]->setId(71);
    this->tiles[23]->setId(72);
    this->tiles[20]->setId(73);
    this->tiles[17]->setId(74);
    this->tiles[52]->setId(81);
    this->tiles[49]->setId(82);
    this->tiles[46]->setId(83);
    this->tiles[43]->setId(84);
    //bases
    this->tiles[70]->setId(101);
    this->tiles[71]->setId(102);
    this->tiles[68]->setId(103);
    this->tiles[69]->setId(104);
    this->tiles[56]->setId(111);
    this->tiles[57]->setId(112);
    this->tiles[59]->setId(113);
    this->tiles[58]->setId(114);
    this->tiles[61]->setId(121);
    this->tiles[60]->setId(122);
    this->tiles[62]->setId(123);
    this->tiles[63]->setId(124);
    this->tiles[66]->setId(131);
    this->tiles[67]->setId(132);
    this->tiles[65]->setId(133);
    this->tiles[64]->setId(134);
}