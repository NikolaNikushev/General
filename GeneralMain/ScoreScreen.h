#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "Player.h"
using namespace std;
class ScoreScreen
{
private:
	vector<Player> finishedPlayers;
	vector<Player> unfinishedPlayers;
	int playerNum;
public:
	ScoreScreen(void);
	~ScoreScreen(void);
	void addFinishedPlayer(Player);
	void addUnfinishedPlayer(Player);

	void printCurrentWinner();
	void printAllWinners();
	void printAllLosers();
	void printCurrentLosers();
	void writeToFile(string, bool, bool);
	void readFromFilePlayersList(bool, bool);
};

