#include "Player.h"
#include "RandomAIPlayer.h"
#include <time.h>
#include <stdlib.h>

RandomAIPlayer::RandomAIPlayer(int pNum)
:Player(pNum)
{
	srand(time(NULL));
}

int RandomAIPlayer::makeMove(int board[9])
{
	return rand() % 9 + 1;
}