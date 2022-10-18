#include "TicTacToe.h"
#include <cstdlib>
#include <cstdio>

int *TicTacToe::getBoard()
{
    return board;
}

TicTacToe::TicTacToe()
{
    for(int i = 0; i < 9; i++)
    {
        board[i] = 0;
    }
    movesLeft = 9;
    turn = true;
    gameDone = 0;
}

void TicTacToe::displayBoard()
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(board[i*3+j] == 1)
            {
                printf(" X");
            }
            else if(board[i*3+j] == -1)
            {
                printf(" 0");
            }
            else
            {
                printf("  ");
            }

            if(j < 2)
            {
                printf(" |");
            }
        }
        printf("\n");
        if(i < 2)
        {
            printf("___|___|___\n");
        }
    }
}

void TicTacToe::move(int pos)
{
    if(board[pos] !=0)
    {
        illegalMove = true;
        movesLeft = 0;
        if(turn)
        {
            P1Reward = -20;
            P2Reward = 0;
        }
        else
        {
            P1Reward = 0;
            P2Reward = -20;
        }
        return;
    }
    if(turn)
    {
        board[pos] = 1;
    }
    else
    {
        board[pos] = -1;
    }
    movesLeft--;
    turn= !turn;
}

bool TicTacToe::isGameDone() {
    if(movesLeft == 0)
    {
        if(!illegalMove)
        {
            P1Reward = 5;
            P2Reward = 5;
        }
        return true;
    }
    else
    {
        int total;
        for(int row = 0; row < 3; row ++)
        {
            total = 0;
            for(int cell = 0; cell < 3; cell++)
            {
                total += board[row * 3 + cell];
            }
            if(total == 3 || total == -3)
            {
                gameDone = (total / 3);

                if(gameDone == 1)
                {
                    P1Reward = 10;
                    P2Reward = -10;
                }
                else
                {
                    P1Reward = -10;
                    P2Reward = 10;
                }
                return true;
            }
        }

        for(int column = 0; column < 3; column ++)
        {
            total = 0;
            for(int cell = 0; cell < 3; cell++)
            {
                total += board[cell*3 + column];
            }
            if(total == 3 || total == -3)
            {
                gameDone = (total / 3);

                if(gameDone == 1)
                {
                    P1Reward = 10;
                    P2Reward = -10;
                }
                else
                {
                    P1Reward = -10;
                    P2Reward = 10;
                }
                return true;
            }
        }
        if(((board[0] == board[4] && board[4] == board[8]) || (board[2] == board[4] && board[4] == board[6])) && board[4] != 0)
        {
            gameDone = (board[4]);

            if(gameDone == 1)
            {
                P1Reward = 10;
                P2Reward = -10;
            }
            else
            {
                P1Reward = -10;
                P2Reward = 10;
            }
            return true;
        }
    }
    return false;
}

bool TicTacToe::getTurn() {
    return turn;
}

int TicTacToe::getGameStatus() {
    return gameDone;
}

int TicTacToe::getP1Reward() {
    return P1Reward;
}
