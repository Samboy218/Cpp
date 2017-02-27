#include <iostream>

using namespace std;

class TicTacToeBoard
{
	public:
		TicTacToeBoard();
		
		//makes a move on the tic tac toe board if possible
		//pre: player represents which player's turn it is; 1 = 'X', 2 = 'O'. move indicates which square they are moving to (index in 1D array)
		//post: returns true if the move was correctly made, false otherwise
		bool playSpot(int player, int move);
		
		//checks to see if the game has ended
		//pre: None
		//post: returns 0 if the game is not over, 1 if 'X' has won, 2 if 'O' has won, and 3 if the game is a draw
		//		returns -1 on an error (very bad)
		int stateCheck();
		
		//returns a copy of what the current board looks like
		//pre: container is an array of exactly 9 ints
		//post: fills 'container' with the current board state
		//	this array represents the board going from left-right, top-bottom, 
		//	and where a 0 indicates empty, 1 indicates an 'X', and a 2 indicates an 'O'
		void getBoard(int container[9]);
		
		//draws the board in a human-readable format
		//pre: None
		//Post: Writes the outputted board to standard out
		void drawBoard();
		
		//resets the board to all 0
		//pre: None
		//post: the board is reset to the beginning of the game condition
		void resetBoard();
	
	private:
		//the board variable
		int board[9];
		
		//checks if a songle player has won
		//pre: player must be either 1 or 2
		//post: returns 0 if the player has not won, 1 if they have, and -1 if an error occurred
		int playerWinCheck(int player);
		
		//chacks if a draw has occurred
		//assumes neither player has won (you've been warned)
		//pre: None
		//post: returns true if the board is in a draw state, false otherwise
		bool drawCheck();
};