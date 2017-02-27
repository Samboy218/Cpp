#include "Player.h"
#include "TicTacToeBoard.h"


class TTTController
{
	public:
		TTTController(Player* player1, Player* player2);
		
		//plays a single game of TicTacToe
		int playGame();
		
		//displays the current statistics of the games played
		void showStats();
		
		unsigned getP1Wins();
		unsigned getP2Wins();
		unsigned getDraws();
		unsigned getGamesPlayed();
	private:
	
		Player* player1;
		Player* player2;
		TicTacToeBoard gameBoard;
		
		unsigned p1wins;
		unsigned p2wins;
		unsigned draws;
		unsigned gamesPlayed;
};