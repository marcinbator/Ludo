#pragma once
#include <SFML/Graphics.hpp>
#include "Random.h"
#include "Board.h"
#include <vector>

using namespace std;
/* PROSTY
G³ównym priorytetem dla AI jest wystawienie jak najwiêkszej iloœci pionków na pole gry. 
Jeœli nie ma mo¿liwoœci wystawienia pionka AI przesuwa losowy pionek, który ma prawid³owy ruch.
*/
/* TRUDNY
Priorytetem jest bicie. AI stara siê utrzymaæ przynajmniej dwa pionki na planszy. Du¿o oczek - ruch dalszym pionem,
ma³o oczek - ruch bli¿szym.
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

