#include "TicTacToe.h"
#include <cstdlib>
#include <cstdio>


#define WINNINGREWARD 10
#define DRAWREWARD 10
#define WINBLOCKREWARD 3


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
    P1Reward = 0;
    P2Reward = 0;
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
            P1Reward += -20;
            P2Reward += 0;
        }
        else
        {
            P1Reward += 0;
            P2Reward += -20;
        }
        return;
    }
    if(isBlockingWin(pos))
    {
        if(turn)
        {
            P1Reward += WINBLOCKREWARD;
            P2Reward += 0;
        }
        else
        {
            P1Reward += 0;
            P2Reward += WINBLOCKREWARD;
        }
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
            P1Reward = DRAWREWARD;
            P2Reward = DRAWREWARD;
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
                    P1Reward += WINNINGREWARD;
                    P2Reward += -WINNINGREWARD;
                }
                else
                {
                    P1Reward += -WINNINGREWARD;
                    P2Reward += WINNINGREWARD;
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
                    P1Reward += WINNINGREWARD;
                    P2Reward += -WINNINGREWARD;
                }
                else
                {
                    P1Reward += -WINNINGREWARD;
                    P2Reward += WINNINGREWARD;
                }
                return true;
            }
        }
        if(((board[0] == board[4] && board[4] == board[8]) || (board[2] == board[4] && board[4] == board[6])) && board[4] != 0)
        {
            gameDone = (board[4]);

            if(gameDone == 1)
            {
                P1Reward += WINNINGREWARD;
                P2Reward += -WINNINGREWARD;
            }
            else
            {
                P1Reward += -WINNINGREWARD;
                P2Reward += WINNINGREWARD;
            }
            return true;
        }
    }
    return false;
}

bool TicTacToe::getTurn() {
    return turn;
}

int TicTacToe::getP1Reward() {
    return P1Reward;
}

bool TicTacToe::isMoveAvailable(int pos) {
    return board[pos] == 0;
}

bool TicTacToe::isGameDone(int *boardCustom) {
    int total;
    for(int row = 0; row < 3; row ++)
    {
        total = 0;
        for(int cell = 0; cell < 3; cell++)
        {
            total += boardCustom[row * 3 + cell];
        }
        if(total == 3 || total == -3)
        {
            gameDone = (total / 3);

            if(gameDone == 1)
            {
                P1Reward += 10;
                P2Reward += -10;
            }
            else
            {
                P1Reward += -10;
                P2Reward += 10;
            }
            return true;
        }
    }

    for(int column = 0; column < 3; column ++)
    {
        total = 0;
        for(int cell = 0; cell < 3; cell++)
        {
            total += boardCustom[cell*3 + column];
        }
        if(total == 3 || total == -3)
        {
            gameDone = (total / 3);

            if(gameDone == 1)
            {
                P1Reward += 10;
                P2Reward += -10;
            }
            else
            {
                P1Reward += -10;
                P2Reward += 10;
            }
            return true;
        }
    }
    if(((boardCustom[0] == boardCustom[4] && boardCustom[4] == boardCustom[8]) || (boardCustom[2] == boardCustom[4] && boardCustom[4] == boardCustom[6])) && boardCustom[4] != 0)
    {
        gameDone = (boardCustom[4]);

        if(gameDone == 1)
        {
            P1Reward += 10;
            P2Reward += -10;
        }
        else
        {
            P1Reward += -10;
            P2Reward += 10;
        }
        return true;
    }

    return false;

}

bool TicTacToe::isBlockingWin(int pos) {
    int * boardCustom = new int[9];
    for(int i = 0; i < 9; i++)
    {
        boardCustom[i] = board[i];
    }

    if(turn)
    {
        boardCustom[pos] = -1;
    }
    else
    {
        boardCustom[pos] = 1;
    }
    bool returnVal = isGameDone(boardCustom);

    delete[] boardCustom;

    return returnVal;
}

int TicTacToe::getWinner() {
    if(gameDone == 1)
    {
        return 'X';
    }
    else
    {
        return '0';
    }
}
