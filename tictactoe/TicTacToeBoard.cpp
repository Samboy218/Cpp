#include "TicTacToeBoard.h"

TicTacToeBoard::TicTacToeBoard()
{
	for (int i = 0; i < 9; i++)
	{
		board[i] = 0;
	}
}

bool TicTacToeBoard::playSpot(int player, int move)
{
	if ( move < 1 || move > 9 || (player != 1 && player != 2) )
		return false;
	else if (board[move - 1] != 0)
		return false;
	else
	{
		board[move - 1] = player;
		return true;
	}
}

int TicTacToeBoard::stateCheck()
{
	//assume game is in session
	bool p1Win = false;
	bool p2Win = false;
	bool draw = false;
	
	if (playerWinCheck(1) == 1)
	{
		p1Win = true;
	}
	if (playerWinCheck(2) == 1)
	{
		p2Win = true;
	}
	
	//if neither player won, check for a draw
	if ((!p1Win && !p2Win))
		draw = drawCheck();
	//both players can't win at the same time, that is an error
	if (p1Win && p2Win)
		return -1;
	//a draw can't happen if a player has won, that is an error
	if ((p1Win || p2Win) && draw)
		return -1;
	
	//player 1 wins
	if (p1Win)
		return 1;
	//player 2 wins
	if (p2Win)
		return 2;
	//its a draw!
	if(draw)
		return 3;
	//the game is still on!
	else
		return 0;
	
}

void TicTacToeBoard::getBoard(int container[9])
{	
	for(int i = 0; i < 9; i++)
	{
		container[i] = board[i];
	}
}

void TicTacToeBoard::drawBoard()
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

void TicTacToeBoard::resetBoard()
{
	for (int i = 0; i < 9; i++)
	{
		board[i] = 0;
	}
}

int TicTacToeBoard::playerWinCheck(int player)
{
	if (board[0] == player && board[0] == board[1] && board[1] == board[2])
		return 1;
	if (board[3] == player && board[3] == board[4] && board[4] == board[5])
		return 1;
	if (board[6] == player && board[6] == board[7] && board[7] == board[8])
		return 1;
	
	if (board[0] == player && board[0] == board[3] && board[3] == board[6])
		return 1;
	if (board[1] == player && board[1] == board[4] && board[4] == board[7])
		return 1;
	if (board[2] == player && board[2] == board[5] && board[5] == board[8])
		return 1;
	
	if (board[0] == player && board[0] == board[4] && board[4] == board[8])
		return 1;
	if (board[2] == player && board[2] == board[4] && board[4] == board[6])
		return 1;
	
	return 0;
}

bool TicTacToeBoard::drawCheck()
{
	for(int i = 0; i < 9; i++)
	{
		if (board[i] == 0)
			return false;
	}
}