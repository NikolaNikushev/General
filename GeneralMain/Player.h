#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Dice.h"
using namespace std;
class Player
{

private:
	int myPoints;
	int cellValues[13][4];
	int currentCommandNum;
	int currentThrow;

	bool usedCells[13][4];
	bool firstThrow;
	bool isPlaying;

	string myName;
	vector<string> availableMovesVector;
	string table [31][9];
	vector<Dice> dices;

public:
	Player(string);
	int getPoints(void);
	void setPoints(int);
	string getName(void);
	void setName(string);


	vector<Dice> getDices(void);

	int getCellValue(int, int);
	int getCurrentThrow(void);

	bool getUsedCell(int, int);
	bool getFirstThrow(void);
	bool getIsPlaying();

	void setIsPlaying(bool);
	void setDices(Dice);
	void clearDices();
	void setCellValue(int, int, int);
	void setCurrentThrow(int);

	void setUsedCell(int, int, bool);
	void setFirstThrow(bool);

	void settable (string);

	void rollDice(void);
	void showTable();

	int sumPoints(void);

	void throwDice(void);

};


