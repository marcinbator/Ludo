#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class Dial;

class Menu
{
protected:
    bool isDisplayed;
    Dial* dial;
    sf::Font font;
    sf::Text title;
public:
    Menu() = delete;
    Menu(int centerX, int centerY);
    ~Menu();

    virtual void draw(sf::RenderWindow* window, int centerX, int centerY);

    virtual bool getIsDisplayed() const;
protected:
    void initMenu(int centerX, int centerY);
    void drawLogo(sf::RenderWindow* window, int centerX, int centerY);
};