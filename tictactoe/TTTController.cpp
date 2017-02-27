#include "TTTController.h"

TTTController::TTTController(Player* p1, Player* p2)
{
	player1 = p1;
	player2 = p2;
	
	p1wins = 0;
	p2wins = 0;
	draws = 0;
	gamesPlayed = 0;
}

//plays a single game of TicTacToe
int TTTController::playGame()
{
	int boardArray[9];
	int move = 0;
	bool valid = true;
	while (true)
	{
		gameBoard.getBoard(boardArray);
		//cout << "Player 1 (X), make a move 1-9\n";
		do
		{
			move = player1->makeMove(boardArray);
			if (!gameBoard.playSpot(1, move))
			{
				valid = false;
				player1->setInvalid(true);
			}
			else
			{
				valid = true;
			}
		}while(!valid);
		
		gameBoard.getBoard(boardArray);
		if (gameBoard.stateCheck() != 0)
			break;
		
		//cout << "Player 2 (O), make a move 1-9\n";
		do
		{
			move = player2->makeMove(boardArray);
			if (!gameBoard.playSpot(2, move))
			{
				valid = false;
				player2->setInvalid(true);
			}
			else
			{
				valid = true;
			}
		}while(!valid);
		
		if (gameBoard.stateCheck() != 0)
			break;
	}
	
	gamesPlayed++;
	gameBoard.resetBoard();
	switch (gameBoard.stateCheck())
	{
		case -1:
		cout << "Oh crap Morty, thats a baaaaad error!\n";
		return -1;
		break;
		
		case 1:
		p1wins++;
		return 1;
		break;
		
		case 2:
		p2wins++;
		return 2;
		break;
		
		case 3:
		draws++;
		return 3;
		break;
	}
	
	
}

//displays the current statistics of the games played
void TTTController::showStats()
{
	cout << "Total number of games played: " << gamesPlayed << endl;
	cout << "Number of draws: " << draws << endl;
	cout << "Number of wins by player 1: " << p1wins << endl;
	cout << "Number of wins by player 2: " << p2wins << endl;
}

unsigned TTTController::getP1Wins()
{
	return p1wins;
}

unsigned TTTController::getP2Wins()
{
	return p1wins;
}

unsigned TTTController::getDraws()
{
	return draws;
}

unsigned TTTController::getGamesPlayed()
{
	return gamesPlayed;
}