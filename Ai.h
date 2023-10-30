#pragma once
#include <SFML/Graphics.hpp>
#include "Random.h"
#include "Board.h"
#include <vector>

using namespace std;
/* PROSTY
G��wnym priorytetem dla AI jest wystawienie jak najwi�kszej ilo�ci pionk�w na pole gry. 
Je�li nie ma mo�liwo�ci wystawienia pionka AI przesuwa losowy pionek, kt�ry ma prawid�owy ruch.
*/
/* TRUDNY
Priorytetem jest bicie. AI stara si� utrzyma� przynajmniej dwa pionki na planszy. Du�o oczek - ruch dalszym pionem,
ma�o oczek - ruch bli�szym.
*/
class Team;
class Board;

class Ai
{
	int level{};
	int dice {};
	int pawnToMoveId{};
	Team* team;
	Board* board;
public:
	Ai() = delete;
	Ai(int level, Team* team, Board* board);
	bool move(int dice, sf::RenderWindow* window);
private:
	int decide();
	vector<int> getPossibleMoves();
	vector<int> checkStrike(vector<int> possible);
	vector<int> selectIfExit(vector<int> possible);
	vector<int> selectFromDice(vector<int> possible);
	int getRandom(vector<int> possible);
	void setNextPawnId();
};

