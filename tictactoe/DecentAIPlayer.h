#include "Player.h"
class DecentAIPlayer : public Player
{
        public:
            //constructor to initialise player
    		//pre: pNum is the player number, 1 = 'X', 2 = 'O'. any other value is invalid
	    	//post: initializes the player variable with 1 if pNum is invalid
            DecentAIPlayer(int pNum);

            //makes a move given the current state of a tictactoe board passed in
    		//pre: board is a valid tictactoe board, an array of 9 ints where each element is 0, 1, or 2
    		//post: an integer is returned representing the value of the move to be made (1-indexed)
    		virtual int makeMove(int board[9]);
        
        private:

            //checks if the opponent can win, and blocks it if so
            //Pre: board is the current augmented board state
            //Post: returns the move to be made if a block is needed (0-indexed), returns -1 otherwise 
            int blockWin(int board[9]);

            //checks to see if there is a winning move, and moves there if so
            //Pre: board is the current augmented board state
            //Post: returns the move to be made if it can win (0-indexed), returns -1 otherwise
            int moveWin(int board[9]);

            //chooses a good move given we can't win or lose this turn
            //Pre: board is the current augmented board state
            //Post: returns a better move than just a random guess (0-indexed)
            int normalMove(int board[9]);

            //changes the values of each space so that arithmetic can be used to find states
            //Pre: board is the current board state
            //Post: returns an array of the same state, but with augmented values (does not change old array)
            void augmentBoard(int board[9], int container[9]);
            
};
