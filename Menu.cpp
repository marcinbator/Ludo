#include "Menu.h"
#include "Team.h"

Menu::Menu()
{
	this->playersAmount = 0;
	this->aiPlayersAmount = 0;
	this->initMenu();
}

void Menu::showWinners(Team** teams, int playersAmount)
{
    system("cls");
    Team* leaderboard[4];
    for (int i = 0; i < playersAmount; i++) {
        if (teams[i]->getStanding() != 0) {
            leaderboard[teams[i]->getStanding()-1] = teams[i];
        }
        else {
            leaderboard[playersAmount-1] = teams[i];
        }
    }
    for (int i = 0; i < playersAmount; i++) {
        cout << "\tMiejsce " + to_string(i+1) << ": " << leaderboard[i]->getName() << endl;
    }
}

int Menu::getPlayersAmount()
{
	return this->playersAmount;
}

int Menu::getAiPlayersAmount()
{
	return this->aiPlayersAmount;
}

//private

void Menu::initMenu()
{
    do {
        cout << "Witaj w grze. Podaj liczbe zywych graczy: ";
        cin >> this->playersAmount;
        cout << "Podaj liczbe graczy SI: ";
        cin >> this->aiPlayersAmount;
        if (this->playersAmount >= 1 && this->playersAmount <= 4 && this->aiPlayersAmount >= 0 && this->aiPlayersAmount <= 4 && this->playersAmount + this->aiPlayersAmount <= 4) { //todo >1
            cout << "Uruchamianie...";
            break;
        }
        else {
            cout << "Blad! Sprawdz warunki - laczna liczba graczy musi byc mniejsza rowna 4, a liczba zywych graczy oraz graczy SI musi byc w zakresie od 1 do 4.\n";
        }
    } while (true);
}