#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;

class Tile;
class Button;
class Dial;
class TossButton;

class Board
{
	int centerX;
	int centerY;
	Dial* dial;
	TossButton* tossButton;
	Button* warp;
	Button* rematch;
	Tile* tiles[72];
	sf::Texture diceTexture;
	sf::Sprite dice;
public:
	const static int TILES_AMOUNT = 72;
	const static int BASE_FIRST_ID = 100;
	const static int BASE_SIZE = 4;
	const static int LAST_TILE = 40;
	const static int TARGET_FIRST_ID = 50;
	const static int TARGET_LAST_ID = 53;

	Board() = delete;
	Board(sf::RenderWindow* window);
	~Board();

	void drawBoard(sf::RenderWindow* window);
	void setDiceTexture(string texturePath);

	int getCenterX() const;
	int getCenterY() const;
	Tile* getTileById(int id) const;
	Button* getWarp() const;
	Button* getRematch() const;
	Dial* getDial() const;
	TossButton* getTossButton() const;
	Tile** getTiles();
private:
	void setCenter(sf::RenderWindow* window);
	void drawLogo(sf::RenderWindow* window);
	void initTiles();
	void initButtons();
	void initBoard();
	void setIds();
};