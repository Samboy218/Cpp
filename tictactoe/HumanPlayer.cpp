#include "Player.h"
#include "HumanPlayer.h"
#include <limits>
#include <iostream>

using namespace std;

HumanPlayer::HumanPlayer(int pNum)
:Player(pNum)
{

}

int HumanPlayer::makeMove(int board[9])
{
	int response = 0;
	if (getInvalid())
	{
		cout << "Last move was invalid!, please enter a valid move for the current board state\n";
		setInvalid(false);
	}
	drawBoard(board);
	switch(getPlayerNum())
	{
		case 1:
		cout << "Here is the board, player 1(X) make a move 1-9\n";
		break;
		
		case 2:
		cout << "Here is the board, player 2(O) make a move 1-9\n";
		break;
		
		default:
		cout << "Here is the board, make a move 1-9\n";
		break;
	}
	do
	{
		if (response > 9 || response < 0)
		{
			cout << "Invalid entry, please enter a number from 1 to 9\n";
		}
		if (cin.fail())
		{
			cout << "Not a number, please enter a number 1-9 this time\n";
			cin.clear();
			cin.ignore(std::numeric_limits<int>::max(), '\n');			
		}
		cin >> response;
	}while(cin.fail() || response > 9 || response < 0);
	
	return response;
}

void HumanPlayer::drawBoard(int board[9])
{
	char symbols[3];
	symbols[0] = ' ';
	symbols[1] = 'X';
	symbols[2] = 'O';
	
	cout<< endl;
	cout << symbols[board[0]] << "|" << symbols[board[1]] << "|" << symbols[board[2]] << endl;
	cout <<"-----" << endl;
	cout << symbols[board[3]] << "|" << symbols[board[4]] << "|" << symbols[board[5]] << endl;
	cout <<"-----" << endl;
	cout << symbols[board[6]] << "|" << symbols[board[7]] << "|" << symbols[board[8]] << endl;
	cout<< endl;
}