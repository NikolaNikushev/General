#include "stdafx.h"
#include "ScoreScreen.h"

ScoreScreen::ScoreScreen(void)
{
	playerNum = 1;
}


ScoreScreen::~ScoreScreen(void)
{
}

void ScoreScreen::writeToFile(string content, bool isLosersList, bool hasFinished){
	
	string path;
	if(isLosersList){
		path = "losers.txt";
	}
	else{
		path = "winners.txt";
	}
	string line;
	int start = 0;
	ifstream olderFile(path);
	if (olderFile.is_open())
	{
		while ( getline (olderFile,line) )
		{
			start++;
		}
		olderFile.close();
	}
	else {
		cout << "Unable to open file" << endl;
	}
	ofstream newFile;
	newFile.open(path, std::ios_base::app);

	if (newFile.is_open())
	{
		newFile <<"Player Number " <<  (start + (playerNum++)) << " -> "<< content << "\n";
		newFile.close();
	}
	else {
		cout << "Unable to open file"<< endl;
	}
}

void ScoreScreen::readFromFilePlayersList(bool isLosersList, bool hasFinishedList){
	string path;
	if(!hasFinishedList){
		cout << "Not finished list:"<<endl;
		path = "notFinished.txt";
	}
	else if(isLosersList){
		cout << "Losers list:"<<endl;
		path = "losers.txt"; 
	}
	else{
		cout << "Winners list:"<<endl;
		path = "winners.txt"; 
	}

	ifstream myfile (path);
	string line;
	if (myfile.is_open())
	{
		while ( getline (myfile,line) )
		{
			cout << line << '\n';
		}
		myfile.close();
	}
	else{
		cout << "Unable to open file"<< endl; 
	}
}

void ScoreScreen::addFinishedPlayer(Player player){
	finishedPlayers.push_back(player);
}

void ScoreScreen::addUnfinishedPlayer(Player player){
	unfinishedPlayers.push_back(player);
}

void ScoreScreen::printCurrentWinner(){
	int maxScore = INT_MIN;
	Player winner("none");
	cout << "The current winner is: ";
	if(finishedPlayers.size()>0){
		for(int i = 0; i < finishedPlayers.size(); i++){
			Player* currentCheckingPlayer = &finishedPlayers.at(i);
			int currentPlayerScore = currentCheckingPlayer -> getPoints();
			if(currentPlayerScore > maxScore){
				maxScore = currentPlayerScore;
				winner = *currentCheckingPlayer;
			}
		}
		string points;
		stringstream convert; 

		convert << winner.getPoints();

		points = convert.str();
		string fileInfo = winner.getName() +  " with score " + points + "\n";
		cout << fileInfo << endl;
		writeToFile(fileInfo, false, true);
	}
	else{
		cout << winner.getName() << endl;
	}
}

void ScoreScreen::printAllWinners(){
	readFromFilePlayersList(false, true);
}

void ScoreScreen::printAllLosers(){
	readFromFilePlayersList(true, true);
}

void ScoreScreen::printCurrentLosers(){
	int maxScore = INT_MIN;
	Player winner("none");
	if(finishedPlayers.size() > 0){
		for(int i = 0; i < finishedPlayers.size(); i++){
			Player* currentCheckingPlayer = &finishedPlayers.at(i);
			int currentPlayerScore = currentCheckingPlayer -> getPoints();
			if(currentPlayerScore > maxScore){
				maxScore = currentPlayerScore;
				winner = *currentCheckingPlayer;
			}
		}
	}
	if(finishedPlayers.size() > 1){
		cout << "The current losers are:" << endl;
		for(int i = 0; i<finishedPlayers.size(); i++){
			Player player = finishedPlayers.at(i);
			if(player.getName() == winner.getName() && player.getPoints() == winner.getPoints()){
				continue;
			}
			else{
				string points;
				stringstream convert; 

				convert << player.getPoints();

				points = convert.str();
				string fileInfo = player.getName() +  " with score " + points + "\n";
				cout << fileInfo << endl;;
				writeToFile(fileInfo, true, true);
			}
		}
	}
	if(unfinishedPlayers.size() > 0){
		cout << "All the unfinished players are:" << endl;
		for(int i = 0; i<unfinishedPlayers.size(); i++){
			Player player = unfinishedPlayers.at(i);
			string points;
			stringstream convert; 

			convert << player.getPoints();

			points = convert.str();
			string fileInfo = player.getName() +  " with score " + points + "\n";
			cout << fileInfo << endl;;
			writeToFile(fileInfo, true, false);
		}
	}
}


