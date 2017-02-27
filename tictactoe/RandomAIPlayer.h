class RandomAIPlayer: public Player
{
	public:
		//constructor to initialise player
		//pre: pNum is the player number, 1 = 'X', 2 = 'O'. any other value is invalid
		//post: initializes the player variable with 1 if pNum is invalid
		RandomAIPlayer(int pNum);
	
		//makes a move given the current state of a tictactoe board passed in
		//pre: board is a valid tictactoe board, an array of 9 ints where each element is 0, 1, or 2
		//post: an integer is returned representing the value of the move to be made
		virtual int makeMove(int board[9]);
	private:
};