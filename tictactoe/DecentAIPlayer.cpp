#include "DecentAIPlayer.h"
#include <time.h>
#include <stdlib.h>

#include <iostream>
using namespace std;

DecentAIPlayer::DecentAIPlayer(int pNum)
:Player(pNum)
{
    srand(time(NULL));
}

int DecentAIPlayer::makeMove(int board[9])
{
    //get augmented board
    int evalBoard[9];
    augmentBoard(board, evalBoard);

    //first, if we can win then do that
    int currMove = moveWin(evalBoard);
    if (currMove != -1)
        return currMove + 1;
    
    //then, we block a move if the opponent will win soon
    currMove = blockWin(evalBoard);
    if (currMove != -1)
        return currMove + 1;

    //then find the next best thing
    currMove = normalMove(evalBoard) + 1;
    return currMove;
}

int DecentAIPlayer::blockWin(int board[9])
{
    int threeSum = 0;

    //we sum all of the values in a line, and since 1=empty, 2=me, and 3=enemy, the sum tells us the outcome
    //11 means the enemy has 2 in a row
    
    //check each row
    for (int i=0; i < 9; i += 3)
    {
        threeSum = board[i] + board[i+1] + board[i+2];
        if (threeSum == 11)
        {
            if (board[i] == 1)
                return i;
            if (board[i+1] == 1)
                return i+1;
            if (board[i+2] == 1)
                return i+2;
        }
    }
    
    //check each column
    for (int i=0; i < 3; i++)
    {
        threeSum = board[i] + board[i+3] + board[i+6];
        if (threeSum == 11)
        {
            if (board[i] == 1)
                return i;
            if (board[i+3] == 1)
                return i+3;
            if (board[i+6] == 1)
                return i+6;
        }
    }

    //check both diagonals
    threeSum = board[0] + board[4] + board[8];
    if (threeSum == 11)
    {
        if (board[0] == 1)
            return 0;
        if (board[4] == 1)
            return 4;
        if (board[8] == 1)
            return 8;
    }

    threeSum = board[2] + board[4] + board[6];
    if (threeSum == 11)
    {
        if (board[2] == 1)
            return 2;
        if (board[4] == 1)
            return 4;
        if (board[6] == 1)
            return 6;
    }

    //no imminient loss
    return -1;
}

int DecentAIPlayer::moveWin(int board[9])
{
    int threeSum = 0;

    //we sum all of the values in a line, and since 1=empty, 2=me, and 3=enemy, the sum tells us the outcome
    //5 means we enemy has 2 in a row
    
    //check each row
    for (int i=0; i < 9; i += 3)
    {
        threeSum = board[i] + board[i+1] + board[i+2];
        if (threeSum == 5)
        {
            if (board[i] == 1)
                return i;
            if (board[i+1] == 1)
                return i+1;
            if (board[i+2] == 1)
                return i+2;
        }
    }
    
    //check each column
    for (int i=0; i < 3; i++)
    {
        threeSum = board[i] + board[i+3] + board[i+6];
        if (threeSum == 5)
        {
            if (board[i] == 1)
                return i;
            if (board[i+3] == 1)
                return i+3;
            if (board[i+6] == 1)
                return i+6;
        }
    }

    //check both diagonals
    threeSum = board[0] + board[4] + board[8];
    if (threeSum == 5)
    {
        if (board[0] == 1)
            return 0;
        if (board[4] == 1)
            return 4;
        if (board[8] == 1)
            return 8;
    }

    threeSum = board[2] + board[4] + board[6];
    if (threeSum == 5)
    {
        if (board[2] == 1)
            return 2;
        if (board[4] == 1)
            return 4;
        if (board[6] == 1)
            return 6;
    }

    //no imminient win
    return -1;
}

int DecentAIPlayer::normalMove(int board[9])
{
    if (board[4] == 1)
    {
        return 4;
    }
    if (board[0] == 1 || board[2] == 1 || board[6] == 1 || board[8] == 1)
    {
        switch(rand()%4 +1)
        {
            case 1:
            return 0;
            break;
            
            case 2:
            return 2;
            break;

            case 3:
            return 6;
            break;

            case 4:
            return 8;
            break;
        }
    }
    else
    {
        switch(rand()%4 + 1)
        {
            case 1:
            return 1;
            break;
            
            case 2:
            return 3;
            break;

            case 3:
            return 5;
            break;

            case 4:
            return 7;
            break;
        }
    }
}

void DecentAIPlayer::augmentBoard(int board[9], int container[9])
{
    for (int i = 0; i < 9; i++)
    {
        if (board[i] == 0)
        {
            container[i] = 1;
        }
        else if (board[i] == getPlayerNum())
        {
            container[i] = 2;
        }
        else
        {
            container[i] = 5;
        }
    }
}
