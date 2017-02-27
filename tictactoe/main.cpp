#include "TTTController.h"
#include "HumanPlayer.h"
#include "RandomAIPlayer.h"
#include "DecentAIPlayer.h"

int main()
{	
	int winner = 0;
	Player* player1 = new HumanPlayer(1);
	Player* player2;
	
	string answer;
	cout << "Do you want a (B)ad opponent? or a (s)mart one?";
	cin >> answer;
	
	if (answer == "s" || answer == "S")
	{
		player2 = new DecentAIPlayer(2);
	}
	else
	{
		player2 = new DecentAIPlayer(2);
	}
	
	TTTController gameMaster(player1, player2);
	
	winner = gameMaster.playGame();
	
	switch (winner)
	{
		case -1:
		cout << "Oh crap Morty, thats a baaaaad error!\n";
		break;
		
		case 1:
		cout << "Congrats player 1 (X), you won!\n";
		break;
		
		case 2:
		cout << "Congrats player 2 (O), you won!\n";
		break;
		
		case 3:
		cout << "Its a draw, drats!\n";
		break;
		
		case 0:
		cout << "dang\n";
		break;
		
		default:
		cout << "Why is this happening???\n";
		break;
	}
	//gameMaster.showStats();
	
	delete player1;
	delete player2;
}