#ifndef PLAYER_H
#define PLAYER_H
class Player
{
	public:
		//constructor to initialise player
		//pre: pNum is the player number, 1 = 'X', 2 = 'O'. any other value is invalid
		//post: initializes the player variable with 1 if pNum is invalid
		Player(int pNum);
		
		//makes a move given the current state of a tictactoe board passed in
		//pre: board is a valid tictactoe board, an array of 9 ints where each element is 0, 1, or 2
		//post: an integer is returned representing the value of the move to be made
		virtual int makeMove(int board[9]) = 0;
		
		//gets the player's ID number. 1 = 'X', 2 = 'O'
		int getPlayerNum();
		
		//setter and getter functions for the invalid flag, which is used to notify the player his/her move is invalid
		void setInvalid(bool invalid);
		bool getInvalid();
	private:
		bool invalid;
		int playerNum;
};
#endif