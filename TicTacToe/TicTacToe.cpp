#include "TicTacToe.h"
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
    turn = true;
    currentMove = 0;
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
    if(turn)
    {
        board[pos] = 1;
    }
    else
    {
        board[pos] = -1;
    }

    turn= !turn;
}

void TicTacToe::move(int *board, int pos, bool turn)
{
    if(turn)
    {
        board[pos] = 1;
    }
    else
    {
        board[pos] = -1;
    }
}


bool TicTacToe::isMoveAvailable(int* board, int pos) {
    return board[pos] == 0;
}

int TicTacToe::isGameDone(int *boardCustom) {
    int total;
    int gameDone = 0;

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

            return gameDone;
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

            return gameDone;
        }
    }
    if(((boardCustom[0] == boardCustom[4] && boardCustom[4] == boardCustom[8]) || (boardCustom[2] == boardCustom[4] && boardCustom[4] == boardCustom[6])) && boardCustom[4] != 0)
    {
        gameDone = boardCustom[4];

        return gameDone;
    }

    total = 0;
    for(int i = 0; i < 9; i++)
    {
        if(boardCustom[i] != 0)
        {
            total++;
        }
    }
    if(total == 9)
    {
        return 0;
    }
    return -10;
}

int TicTacToe::minimax(int *board, bool maxing)
{
    int gameWinner = isGameDone(board);
    if(gameWinner != -10)
    {
        return gameWinner;
    }

    if(maxing)
    {
        int value = -100;
        for(int i = 0; i < 9; i++)
        {
            if(isMoveAvailable(board, i))
            {
                move(board, i, maxing);
                int nextValue = minimax(board, false);
                board[i] = 0;
                if(nextValue > value)
                {
                    value = nextValue;
                }
            }
        }
        return value;
    }
    else
    {
        int value = 100;
        for(int i = 0; i < 9; i++)
        {
            if(isMoveAvailable(board, i))
            {
                move(board, i, maxing);
                int nextValue = minimax(board, true);
                board[i] = 0;
                if(nextValue < value)
                {
                    value = nextValue;
                }
            }
        }
        return value;
    }

}

int TicTacToe::aiMove()
{
    int bestScore;
    if(turn)
    {
        bestScore = -100;
    }
    else
    {
        bestScore = 100;
    }
    int finalMove = 0;
    for(int i = 0; i < 9; i++)
    {
        if(isMoveAvailable(this->board, i))
        {
            move(this->board, i, turn);
            int score = minimax(this->board, !turn);
            this->board[i] = 0;
            if(turn)
            {
                if(score > bestScore)
                {
                    bestScore = score;
                    finalMove = i;
                }
            }
            else
            {
                if(score < bestScore)
                {
                    bestScore = score;
                    finalMove = i;
                }
            }
        }
    }
    return finalMove;
}
