// GeneralMain.cpp : Defines the entry point for the console application.
// Rules of General:
//You throw 5 dices, that can make different combinations for ones, twos, threes, fours, fives, sixes
//and there are Min and Max values, as well as 5 special fields:
//threes (3 of a kind) with a bonus of 20,
//Kare ( 1 thrue 5 or 2 thrue 6) with a bonus of 30,
//Flush( 3 same dice and 2 same dice ( 3, 3 ,3, 5, 5 )with a bonus of 40 points,
//Khenta ( 4 of a kind ) with a bonus of 50 points,
//General ( 5 of a kind ) with a bonus of 60 points
//
//Points: points are a sum of the dices ammount, example 3,3,3,2,2 = 13 points
//and the player can write these points to a field where he wants and has the possibility
//
//Scoring and result of points:
//The first 36 fields containing from 1 to 6 are a sum of each field points, there is a column bonus if the score is above 60, 30 points are added to that column
//then there are the Min and Max, the max is substracted with the min and the sum is multiplyed by the points of the field of ones that is in the column 
//the special fields are fields with points and their total is summed to the end result.
//the total of the player is then summed from all the values.

//Winning: A player wins by having the most points, if a player quits before the game has finished he loses.

#include "stdafx.h"
#include <iostream>
#include "Engine.h"
using namespace std;

int main(int argc, _TCHAR* argv[])
{
	start :
	system("cls");
	int numOfPlayers = 0;
	cout << "How many players will be playing: ";
	cin >> numOfPlayers;
	Engine engine(numOfPlayers);
	engine.start();
	engine.draw();
	system("pause");
	goto start;
	return 0;
}