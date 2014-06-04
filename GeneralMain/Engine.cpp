#include "stdafx.h"

#include "Engine.h"

Player currentPlayer("none");
Engine::Engine(int playersCount)
{
	scoreScreen = ScoreScreen();
	playerCount = playersCount;
	currentCommandNum = 0;
}

void Engine::clearConsole(){
	system("cls");
}

//Prints on the console the current player table of fields with points,
//the current player dice and the available moves, combinations that he has made
//with his dice and the possible points that he can write down to his table.
//Prints the possible navigation that the player can do, select his points,
//select the dice that he wants to keep for the throw, or quit the game.

void Engine::draw()
{
	if(!currentPlayer.getIsPlaying()){
		return;
	}
	clearConsole();
	cout << currentPlayer.getName() << endl;
	currentPlayer.showTable();
	cout << endl;
	dices = currentPlayer.getDices();
	printDices(dices);
	getCombinations();
	string availableMovesResponse = getAvailableMoves();
	cout << availableMovesResponse << endl;
	if(availableMovesVector.size() == 0){
		quitScreen(true);
	}
	if(!playersPlaying()){
		return;
	}
	else{
		cout << "Q) Select points to write.\n";
		int currentThrow = currentPlayer.getCurrentThrow();
		if(currentThrow < 3){
			cout << "W) Select dice to keep/unkeep.\n";
			cout << "E) Throw dice.\n";
		}
		cout << "ESC to exit" << endl;
		char key;
		do{
			key = _getch();
			switch(key){
				case 'q':
					selectPoints();
					break;
				case 'w':
					if(currentThrow < 3){
						selectDice();
					}
					break;
				case 'e':
					if(currentThrow < 3){
						currentPlayer.throwDice();
						availableMovesVector.clear();
						draw();
					}
					break;
				
			}
		}while((key != 27 || availableMovesVector.size() == 0) && playersPlaying());
		if(availableMovesVector.size() == 0 && !playersPlaying()){
			return;
		}
		else if(!playersPlaying()){
			return;
		}
		else{
			quitScreen(false);
		}
	}
}

//Quits the game for the current player and changes to the next player
//if there are no other players left the game ends and the endgame results
//are printed to the console.

void Engine::quitScreen(bool isFinished)
{
	string result;
	int points = currentPlayer.sumPoints();
	currentPlayer.setPoints(points);
	stringstream convert; 

	convert << points;

	result = convert.str();
	string contentToWriteToFile;
	contentToWriteToFile = currentPlayer.getName() + " with score of: " + result;
	if(isFinished){
		cout << currentPlayer.getName() <<"! You finished the game! Your score is: " << result << endl;
		scoreScreen.addFinishedPlayer(currentPlayer);
	}else{
		cout << currentPlayer.getName() <<"! You did not finished the game! Your score is: " << result << endl;
		scoreScreen.addUnfinishedPlayer(currentPlayer);
	}
	Sleep(2000);
	currentPlayer.setIsPlaying(false);
	players.at(playerId) = currentPlayer;
	
	if(nextPlayer()){
		draw();
	}
	else{
		clearConsole();
		scoreScreen.printCurrentWinner();
		scoreScreen.printCurrentLosers();
		Sleep(3000);
		scoreScreen.printAllWinners();
		scoreScreen.printAllLosers();
		return;
	}
}

//starts the game, setting all players info, and the names from the console.

void Engine::start()
{
	playerId = -1;
	cout << "Please enter the player names:" << endl;
	string fix;
	getline(cin,fix);
	for(int i = 1; i < playerCount+1; i++){
		
		string name;
		cout << "Enter Player "<< i << " name: ";
		getline(cin, name);

		Player player(name);
		
		vector<Dice> dices;
		for(int k = 0; k < 5; k++){
			Dice dice;
			player.setDices(dice);
		}

		for(int o = 0; o < 13; o++){
			for(int j=0;j < 4;j++)
			{
				player.setUsedCell(o, j, false);
				player.setCellValue(o, j, 0);
			}
		}
		player.setIsPlaying(true);
		players.push_back(player);
	}
	if(nextPlayer()){
		draw();
	}
}

void Engine::selectDice()
{
	clearConsole();
	availableMovesVector.clear();
	cout << "selecting dice ceperated by ( space ) " << endl;
	cout << "if kept they will be unkept" << endl;
	cout << "dice - value" << endl;
	for(int i = 0; i < 5; i++){
		generateDicePick(i);
	}
	cout << "B for back" << endl;
	cout << "Your dice to keep or B: ";
	string input;
	getline(cin, input);
	if(input.length() == 0){
		getline(cin, input);
	}
	for(unsigned int i = 0; i< input.length(); i++){
		string value = "";
		while(true)
		{
			if( i > input.length() || input[i] ==' ' ||  input[i] == 'b')
				break;
			value += input[i];
			i++;
		}
		if(!(i > input.length()))
			if(input[i] == 'b'){ break;}
		int numb;
		istringstream ( value ) >> numb;
		if(numb > 5 || numb < 1){
			cout << "You entered wrong input!!!" << endl;
			Sleep(2000);
			break;
		}
		if(dices[numb-1].getIsKept() == true){
			dices[numb-1].unKeep();
		}
		else{
			dices[numb-1].keep();
		}
	}
	currentPlayer.clearDices();
	for(unsigned i = 0; i <dices.size(); i++){
		Dice dice = dices.at(i);
		currentPlayer.setDices(dice);
	}
	draw();
}

//Checks if there are any players playing, if so, returns true

bool Engine::playersPlaying(){
	for(unsigned i = 0; i < players.size();i++){
		if(players.at(i).getIsPlaying()){
			return true;
		}
	}
	return false;
}

//Switches to the next player rif he is still ingame and has not quit or finished the game.
bool Engine::nextPlayer(){
	if(playersPlaying()){
		if(playerId >= 0 && players.at(playerId).getIsPlaying()){
			currentPlayer.setCurrentThrow(0);
			
			players.at(playerId) = currentPlayer;
		}
		if(playerId + 1 >= players.size()){
			playerId = 0;
		}
		else{
			playerId++;
		}
		if(players.at(playerId).getIsPlaying()){
			currentPlayer = players.at(playerId);
			currentPlayer.throwDice();
			return true;
		}
		else{
			return nextPlayer();
		}
	}
	else{
		return false;
	}
}

//Shows the dialog if a dice is kept or not

void Engine::generateDicePick(int num){
	Dice dice = dices.at(num);
	string kept = "";
	if(dice.getIsKept()){
		kept = "yes";
	}
	else{
		kept = "no";
	}
	cout << "  " << num+1 << " - " << dice.getCurrentValue() << " kept = " << kept << endl;
}

//Player selects the possible option from his possible moves and combinations, from which he can keep and sign to his table.

void Engine::selectPoints()
{
	cout << "I select: ";
	int selectedPoints = 0;
	string input = "";
	while(input.length() == 0){
		getline(cin, input);
	}
	istringstream ( input ) >> selectedPoints;
	//checks if the input is valid and if it is withing the possible moves that are found

	if(selectedPoints == 0){
		cout << "Your input was invalid! --> " << input << endl;
		Sleep(2000);
		draw();
	}
	else if(selectedPoints-1 < availableMovesVector.size() && selectedPoints > -1){
		string cellAndPoints = availableMovesVector.at(selectedPoints-1);
		int row, col, points;
		int foundItems = 0;
		string value = "";
		
		//from the input it takes the values from the vector of info containing the row, col and points to be writen in the table

		for(unsigned i = 0; i < cellAndPoints.length(); i++){
			while(true){
				if( i >= cellAndPoints.length()){
					break;
				}
				char stringChar = cellAndPoints[i];
				if(stringChar == ' '){
					break;
				}
				else{
					value += stringChar;
					i++;
				}
			}
			
			foundItems++;
			if(foundItems == 1){
				istringstream ( value ) >> row;
			}
			if(foundItems == 2){
				istringstream ( value ) >> col;
			}
			if(foundItems == 3){
				istringstream ( value ) >> points;
			}
			value = "";
		}
		row -= 1;
		col -= 1;
		currentPlayer.setCellValue(row, col, points);
		currentPlayer.setUsedCell(row, col, true);
		availableMovesVector.clear();

		if(nextPlayer()){
			draw();
		}
	}
	else{
		cout << "Your input was invalid! -->" << input << endl;
		Sleep(2000);
		draw();
	}
}

// [[[[[[[[[[[[[[[[[            moves logic            ]]]]]]]]]]]]]]]]]
	
string Engine::getAvailableMoves()
{
	string response = "Your available moves are: \n";
	currentCommandNum = 1;
	for(int i=0; i<6; i++)
	{
		int value = numbs[i];
		if(value >= 1)
		{
			int points = value *(i+1);
			switch(i+1)
			{
			case 6:
				response += "SIXES: \n";
				response += checkNumbersRowsAndGiveAvailable(5, points);
				break;
			case 5:
				response += "FIVES: \n";
				response += checkNumbersRowsAndGiveAvailable(4, points);
				break;
			case 4:
				response += "FOURS: \n";
				response += checkNumbersRowsAndGiveAvailable(3, points);
				break;
			case 3:
				response += "THREES: \n";
				response += checkNumbersRowsAndGiveAvailable(2, points);
				break;
			case 2:
				response += "TWOS: \n";
				response += checkNumbersRowsAndGiveAvailable(1, points);
				break;
			case 1:
				response += "ONES: \n";
				response += checkNumbersRowsAndGiveAvailable(0, points);
				break;
			}
		}
		if(value == 3)
		{
			response += "THREE OF A KIND: \n";
			response += checkForTriples(8, value*(i+1) + 20);
		}
		if(value == 4)
		{
			response += "FLUSH: \n";
			response += checkForFlushs(10, value*(i+1) + 40);
		}
		if(value == 5)
		{
			response += "GENERAL: \n";
			response += checkForGeneral(12, value*(i+1) + 60);
		}
	}
	int value = numbs[0] + numbs[1] + numbs[2] + numbs[3] + numbs[4] + numbs[5];
		if(value == 5)
		{
			if(numbs[1] == 1 && numbs[2] == 1 &&numbs[3] == 1 &&numbs[4] == 1 &&numbs[5] == 1)
			{
				response += "STREIGHT:\n";
				response += checkFoStreight(9, 50);
			}
			else if(numbs[0] == 1 && numbs[1] == 1 &&numbs[2] == 1 &&numbs[3] == 1 &&numbs[4] == 1)
			{
				response += "STREIGHT:\n";
				response += checkFoStreight(9, 45);
			}
			int first = 0, second = 0;
			for(int k = 0; k < 6; k++)
			{
				if(numbs[k] == 2)
					first = (k+1)*numbs[k];
				if( numbs[k] == 3)
					second = (k+1)*numbs[k];
				if(first > 0 && second > 0)
					break;
			}
			if(first > 0 && second > 0){
				response += "KHENTA:\n";
				response += checkForKhenta(11, first+second + 50);
			}
		}
	value = numbs[0]*1 + numbs[1]*2 + numbs[2]*3 + numbs[3]*4 + numbs[4]*5 + numbs[5]*6;
	response +=  checkMinAndMaxAndReturnIfAvailable(value);
	if(availableMovesVector.size() == 0){
		response += "FORCE TO PLACE X FOR 0 POINTS\n";
		response += forceToPlaceX();
	}
	return response;
}

string Engine::checkForTriples(int row, int points)
{
	string response;
	for(int i = 0; i < 4; i++)
	{
		response += checkCellAndGetCoordinates( row, i, points, false, false);
	}
		
	return response;
}

string Engine::checkFoStreight(int row, int points)
{
	string response;
		
	for(int i = 0; i < 4; i++)
	{
		response += checkCellAndGetCoordinates( row, i, points, false, false);
	}
		
	return response;
}

string Engine::checkForFlushs(int row, int points)
{
	string response;
		
	for(int i = 0; i < 4; i++)
	{
		response += checkCellAndGetCoordinates( row, i, points, false, false);
	}

	return response;
}

string Engine::checkForKhenta(int row, int points)
{
	string response;
		
	for(int i = 0; i < 4; i++)
	{
		response += checkCellAndGetCoordinates( row, i, points, false, false);
	}

	return response;
}

string Engine::checkForGeneral(int row, int points)
{
	string response;
		
	for(int i = 0; i < 4; i++)
	{	
		response += checkCellAndGetCoordinates( row, i, points, false, false);
	}
		
	return response;
}

string Engine::checkMinAndMaxAndReturnIfAvailable(int points)
{
	string response;
		
	for(int row = 6; row <= 7; row++)
	{
		for(int i = 0; i < 4; i++)
		{
			if(row == 6)
				response += checkCellAndGetCoordinates( row, i, points,true, false);
			else
				response += checkCellAndGetCoordinates( row, i, points,false, true);
		}
	}
	return response;
}

string Engine::checkNumbersRowsAndGiveAvailable(int row, int points)
{
	string response = "";
	for(int i = 0; i < 4; i++)
	{
		if(row <= 6)
		{
			response += checkCellAndGetCoordinates( row, i, points, false, false);
		}
	}
	return response;
}

// [[[[[[[[[[[[[[[[[            moves logic end           ]]]]]]]]]]]]]]]]]


// sets the ammount of same dice with given value 
void Engine::getCombinations()
{
	for(int i =0; i< 6; i++)
		numbs[i] = 0;
	int count = 0;
	for(int i = 0; i < 5; i++)
	{
		switch(dices.at(i).getCurrentValue())
		{
		case 1:
			numbs[0]++;
			break;
		case 2:
			numbs[1]++;
			break;
		case 3:
			numbs[2]++;
			break;
		case 4:
			numbs[3]++;
			break;
		case 5:
			numbs[4]++;
			break;
		case 6:
			numbs[5]++;
			break;
		}
	} 
}

string Engine::checkCellAndGetCoordinates(int row,int  col, int points, bool isMax, bool isMin)
{
	string response = "";
	bool usedCell = currentPlayer.getUsedCell(row,col);
	if(!usedCell)
	{
		ostringstream convert;   
		convert << currentCommandNum;     
		response = convert.str() + " -- >";   	
		if(isMax){
			response += " MAX -- >";  
		}
		else if(isMin){
			response += " MIN -- >";  
		}
			
		bool responseIsUsed = false;
			
		if(col == 3 && currentPlayer.getFirstThrow())
		{
			response += ("ANNOUNCE: ");
		}
		if(col==2 && row != 12)
		{
			bool lowerCell = currentPlayer.getUsedCell(row+1 , col);
			if(lowerCell)
			{
				//UP
				availableMoves[row+1][col] = true;
				response += generateResponse(row, col, points);
					
				responseIsUsed = true;
			}
		}
		else if(col==0 && row != 0)
		{
			bool upperCell = currentPlayer.getUsedCell(row-1 , col);
			if(upperCell)
			{
				//down
				response += generateResponse(row, col, points);
				availableMoves[row-1][col] = true;

				responseIsUsed = true;
			}
		}
		else
		{
			response += generateResponse(row, col, points);
			availableMoves[row][col] = true;

			responseIsUsed = true;
		}
		if(responseIsUsed){
			currentCommandNum++;
		}
		else{
			return "";
		}
	}
	return response;
}

//generates the possible cells that can be used as a move
string Engine::generateResponse(int row, int col, int points)
{
	ostringstream convert1, convert2, convert3;   
	string response = ("row: "); 
	convert1 << row+1;     
	response += (convert1.str());

	response += (", col: ");
	convert2 << col+1;     
	response += (convert2.str());

	response += (" for ");
  
	convert3 << points;     
	response += (convert3.str());

	response += (" points. \n");
	availableMovesVector.push_back(convert1.str() + " " + convert2.str() + " " + convert3.str());
	return response;
}

//when there are no possible moves forces the player to place an "X" or 0 points to a field
string Engine::forceToPlaceX(){
	string response = "";
	for(int row = 0; row < 13; row++){
		for(int col = 0; col < 4; col++){
			response += checkCellAndGetCoordinates(row, col, 0, false, false);
		}
	}
	return response;
}

void Engine::printDices(vector<Dice> dicesVector){
	vector<Dice> playerDices = dicesVector;
	for(unsigned i = 0; i < playerDices.size(); i++){
		cout << "-----  ";
	}
	cout << endl;

	for(unsigned i = 0; i < playerDices.size(); i++){
		cout << "| " << playerDices.at(i).getCurrentValue() << " |  ";
	}
	cout << endl;

	for(unsigned i = 0; i < playerDices.size(); i++){
		cout << "-----  ";
	}
	cout << endl;
}