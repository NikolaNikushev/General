#include "stdafx.h"
#include "Player.h"

	Player::Player(string name)
	{
		myName = name;
		myPoints = 0;

		firstThrow = true;
		currentThrow = 0;

		for(int i = 0; i < 13; i++){
			for(int j = 0; j < 4; j++){
				cellValues[i][j] = 0;
			}
		}

	}

	int Player::getPoints(){
		return myPoints;
	}

	void Player::setPoints(int points){
		myPoints = points;
	}

	string Player::getName(){
		return myName;
	}

	void Player::setName(string name){
		myName = name;
	}

	vector<Dice> Player::getDices(){
		return dices;
	}

	int Player::getCellValue(int row, int col){
		return cellValues[row][col];
	}

	int Player::getCurrentThrow(void){
		return currentThrow;
	}

	bool Player::getUsedCell(int row, int col){
		return usedCells[row][col];
	}

	bool Player::getFirstThrow(void){
		return firstThrow;
	}

	void Player::setDices(Dice dice){
		dices.push_back(dice);
	}

	void Player::clearDices(){
		dices.clear();
	}

	void Player::setCellValue(int row, int col, int points){
		 cellValues[row][col] = points;
	}

	void Player::setCurrentThrow(int value){
		currentThrow = value;
	}
	void Player::setFirstThrow(bool value){
		firstThrow = value;
	}

	void Player::setUsedCell(int row, int col, bool value){
		usedCells[row][col] = value;
	}

	void Player::rollDice(){
		for(int i = 0; i < 5; i++){
			dices[i].rollDice();
		}
	}

	//prints the player table with current points
	void Player::showTable(){
		int row = -1, col = 0;
		for(int i = 0; i < 31; i++){
			if( i == 13 || i == 19 ){
				i++;
			}
			if(i % 2 == 1){
				row++;
				col = 0;
			}
			for(int j = 0; j < 9; j++){
				if( i == 0 || i % 2 == 0){
					table[i][j] = '-';
				}
				else{
					if( i != 0 && i != 30){
						if((j == 0 || j % 2 == 0)){
							table[i][j] = '|';
						}
						else{
							int cellValue = cellValues[row][col];
							
							if(cellValue == 0 && usedCells[row][col] == false){
								table[i][j] = "   ";
							}
							else{
								string result;

								stringstream convert; 

								convert << cellValue;

								result = convert.str();
								table[i][j] = " " + result + " ";
							}
							col ++;
						}
					}
				}
			}
		}
		for(int i = 0; i< 31; i++){
			for(int j = 0; j < 9; j++){
				cout << table[i][j];
			}
			cout << endl;
		}
	}

	//sums the player points and adds bonuses
	int Player::sumPoints(){
	
		int points = 0;
		
		for(int j = 0; j < 4; j++){
			int colPoints = 0;
			bool givenBonus = false;
			for(int i = 0; i < 6; i++){
				colPoints += cellValues[i][j];
				if(colPoints >= 60 && !givenBonus){
					colPoints += 30;
					givenBonus = true;
				}
			}
			points += colPoints;
		}
		
		for(int j = 0; j<4; j++){
			int minMaxPoints = 0;
			minMaxPoints = (cellValues[6][j] - cellValues[7][j]) * cellValues[0][j];
			points += minMaxPoints;
		}
		for(int i = 8; i < 13 ; i++){
			for(int j = 0; j< 4; j++){
				int specValue = cellValues[i][j];
				points += specValue;
			}
		}
		return points;
	
	}

	void Player::throwDice(){
		if(currentThrow == 1){
			firstThrow = true;
		}
		else{
			firstThrow = false;
		}
		currentThrow++;
		for(int i = 0; i< 5; i++)
			dices[i].rollDice();

	}

	bool Player::getIsPlaying(){
		return isPlaying;
	}

	void Player::setIsPlaying(bool value){
		isPlaying = value;
	}

