#include "Player.h"

Player::Player(int pNum)
{
	invalid = false;
	if (pNum > 2 || pNum < 1)
		playerNum = 1;
	else
		playerNum = pNum;
		
}

int Player::getPlayerNum()
{
	return playerNum;
}

void Player::setInvalid(bool isInvalid)
{
	invalid = isInvalid;
}

bool Player::getInvalid()
{
	return invalid;
}