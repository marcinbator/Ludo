#include "Menu.h"
#include "Team.h"

Menu::Menu()
{
	this->players = 0;
	this->si = 0;
	this->initMenu();
}

void Menu::showWinners(Team** teams, int players)
{
    system("cls");
    Team* leaderboard[4];
    for (int i = 0; i < players; i++) {
        if (teams[i]->getPlace() != 0) {
            leaderboard[teams[i]->getPlace()-1] = teams[i];
        }
        else {
            leaderboard[players-1] = teams[i];
        }
    }
    for (int i = 0; i < players; i++) {
        cout << "\tMiejsce " + to_string(i+1) << ": " << leaderboard[i]->getName() << endl;
    }
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