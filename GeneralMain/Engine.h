#include <string>
#include <vector>
#include "Player.h"
#include "ScoreScreen.h"
#include <iostream>
#include <string>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <conio.h>
using namespace std;
class Engine
{
	private:
	ScoreScreen scoreScreen;
	vector<Player> players;
	int playerCount;
	
	int currentCommandNum;
	bool availableMoves[13][4];
	vector<string> availableMovesVector;
	int numbs[6];
	int playerId;
	vector<Dice> dices;
	public:
	
	Engine(int);

	void clearConsole(void);

	void draw(void);

	void selectPoints();
	

	bool nextPlayer(void);
		
	void selectDice(void);

	void quitScreen(bool);
	
	void start(void);
	
	// [[[[[[[[[[[[[[[[[            moves logic            ]]]]]]]]]]]]]]]]]
	
	string getAvailableMoves();

	string checkForTriples(int , int );
	

	string checkFoStreight(int , int );
	

	string checkForFlushs(int , int );
	

	string checkForKhenta(int , int );
	

	string checkForGeneral(int , int );
	

	string checkMinAndMaxAndReturnIfAvailable(int );
	

	string checkNumbersRowsAndGiveAvailable(int , int );
	
	void getCombinations(void);
	

	string checkCellAndGetCoordinates(int ,int  , int , bool , bool );
	

	string generateResponse(int , int , int );
	

	string forceToPlaceX();

	void generateDicePick(int);

	void printDices(vector<Dice>);

	bool playersPlaying(void);
};