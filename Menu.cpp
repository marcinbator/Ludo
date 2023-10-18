#include "Menu.h"

Menu::Menu()
{
	this->players = 0;
	this->si = 0;
	this->initMenu();
}

int Menu::getPlayers()
{
	return this->players;
}

int Menu::getSi()
{
	return this->si;
}

//private

void Menu::initMenu()
{
    do {
        cout << "Witaj w grze. Podaj liczbe zywych graczy: ";
        cin >> this->players;
        cout << "Podaj liczbe graczy SI: ";
        cin >> this->si;
        if (this->players >= 1 && this->players <= 4 && this->si >= 0 && this->si <= 4 && this->players + this->si <= 4) {
            cout << "Uruchamianie...";
            break;
        }
        else {
            cout << "Blad! Sprawdz warunki - laczna liczba graczy musi byc mniejsza rowna 4, a liczba zywych graczy oraz graczy SI musi byc w zakresie od 1 do 4.\n";
        }
    } while (true);
}