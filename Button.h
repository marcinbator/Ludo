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

	sf::Sprite getSprite() const;
	sf::Text getText() const;
	inline bool isClicked(sf::Event event) const {
		return this->sprite
			.getGlobalBounds()
			.contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
	}
protected:
	void initSprite(string texturePath, int x, int y);
	void initText(string text, int x, int y);
};
