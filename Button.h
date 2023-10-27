#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;

class Button
{
protected:
	sf::Font font;
	sf::Text text;
	sf::Texture texture;
	sf::Sprite sprite;
public:
	Button() = delete;
	Button(string text, string texturePath, int x, int y);

	void draw(sf::RenderWindow* window);
	void setText(sf::Text text);
	void setTexture(string texturePath);

	const sf::Sprite getSprite() const;
	const sf::Text getText() const;
	const bool isClicked(sf::Event event) const;
protected:
	void initSprite(string texturePath, int x, int y);
	void initText(string text, int x, int y);
};
