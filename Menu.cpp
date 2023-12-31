#include "Menu.h"
#include "Dial.h"

Menu::Menu(int centerX, int centerY)
{
    this->isDisplayed = true;
    this->dial = new Dial("Witaj w grze!", centerX, centerY - 80);
    this->initMenu(centerX, centerY);
}

Menu::~Menu()
{
    delete this->dial;
}

void Menu::draw(sf::RenderWindow* window, int centerX, int centerY)
{
    window->draw(this->background);
    this->dial->draw(window);
    this->drawLogo(window, centerX, centerY);
}

bool Menu::getIsDisplayed() const
{
    return this->isDisplayed;
}

void Menu::initBackground(int centerX, int centerY)
{
    this->bgTexture.loadFromFile(string(TEXTURE_PATH) + "bg2.png");
    this->background.setTexture(this->bgTexture);
    this->background.setOrigin(this->background.getGlobalBounds().width / 2, this->background.getGlobalBounds().height / 2);
    this->background.setPosition(centerX, centerY);
}

void Menu::initMenu(int centerX, int centerY)
{
    this->font.loadFromFile(string(FONTS_PATH)+"YoungSerif-Regular.ttf");
    this->title = sf::Text("Menu", this->font, 30);
    this->title.setFillColor(sf::Color::White);
    this->title.setOrigin(this->title.getGlobalBounds().width / 2, this->title.getGlobalBounds().height / 2);
    this->title.setPosition(centerX, centerY - 130);
}

void Menu::drawLogo(sf::RenderWindow* window, int centerX, int centerY)
{
    sf::Texture texture;
    texture.loadFromFile(string(TEXTURE_PATH) + "logo.png");
    sf::Sprite sprite(texture);
    sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
    sprite.setPosition(centerX, centerY - 40 * 9);
    sprite.setScale(0.3, 0.3);
    window->draw(sprite);
}