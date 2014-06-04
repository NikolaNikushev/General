#include <iostream>
#include <ctime>
#include <random>
using namespace std;
class Dice
{
private:
	int currentValue;
	bool isKept;
public:
	Dice();


	int rollDice(void);


	int getCurrentValue(void);

	
	bool getIsKept(void);


	void keep(void);


	void unKeep(void);

};
