#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#include "TicTacToe/TicTacToe.h"
#include "BrainLib/BrainFart.h"

void minimaxTest()
{
    TicTacToe* game = new TicTacToe();

    while(TicTacToe::isGameDone(game->board) == -10)
    {
        if(game->turn)
        {
            int move;
            printf("Your Move: \n");
            scanf("%d", &move);
            game->move(move);
        }
        else
        {
            printf("Minimax Move:\n");
            game->move(game->aiMove());
        }
        game->displayBoard();
    }
}


std::vector<float> BoardToVec(int* arr, int size)
{
    std::vector<float> vec(size);
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            switch(i)
            {
                case 0:
                    if(arr[j] == 1)
                    {
                        vec[i*9+j] = 1;
                    }
                    else
                    {
                        vec[i*9+j] = 0;
                    }
                    break;
                case 1:
                    if(arr[j] == -1)
                    {
                        vec[i*9+j] = 1;
                    }
                    else
                    {
                        vec[i*9+j] = 0;
                    }
                    break;
                case 2:
                    if(arr[j] == 0)
                    {
                        vec[i*9+j] = 1;
                    }
                    else
                    {
                        vec[i*9+j] = 0;
                    }
                    break;
            }

        }
    }

    return vec;
}

std::vector<float> moveVect(int pos, int size)
{
    std::vector<float> moveVect(size);
    for(int i = 0; i < 9; i++)
    {
        moveVect[i] = 0;
    }
    moveVect[pos] = 1;

    return moveVect;
}

int getMove(TicTacToe* game, std::vector<float> guess)
{
    float bestScore = -1;
    int bestMove = 0;
    for(int i = 0; i < 9; i++)
    {
        if(guess[i] > bestScore)
        {
            if(TicTacToe::isMoveAvailable(game->board, i))
            {
                bestScore = guess[i];
                bestMove = i;
            }
        }
    }
    return bestMove;
}

int main()
{
    srand(time(NULL));
    BrainFart* TicTacToePlayer = new BrainFart({27, 18, 18, 9}, 0.07);

    for(int i = 0; i < 1000; i++)
    {
        printf("Training n %d\n", i);
        TicTacToe* game = new TicTacToe();
        int moves = rand()%5 + 3;
        for(int j = 0; j < moves; j++)
        {
            int moveRandomizer = rand() % 11;
            if(moveRandomizer < 3)
            {
                game->move(game->aiMove());
            }
            else
            {
                int randomMove;
                do
                {
                    randomMove = rand()%9;
                }while(!TicTacToe::isMoveAvailable(game->board, randomMove));
                game->move(randomMove);
            }
        }

        TrainingStruct training;

        training.Data = BoardToVec(game->board, 27);

        training.answer = moveVect(game->aiMove(), 9);

        if(TicTacToe::isGameDone(game->board) == -10)
        {
            TicTacToePlayer->train(training);
        }
        else
        {
            i--;
        }


        delete game;
    }

    TicTacToe* finalTestMinimax = new TicTacToe();

    while(TicTacToe::isGameDone(finalTestMinimax->board) == -10)
    {
        if(finalTestMinimax->turn)
        {
            printf("Network Move:\n");
            std::vector<float> answer = TicTacToePlayer->feedForward(BoardToVec(finalTestMinimax->board, 27));
            int move = getMove(finalTestMinimax, answer);
            finalTestMinimax->move(move);
        }
        else
        {
            printf("Minimax Move:\n");
            finalTestMinimax->move(finalTestMinimax->aiMove());
        }
        finalTestMinimax->displayBoard();
    }

    TicTacToe* finalTestReal = new TicTacToe();

    while(TicTacToe::isGameDone(finalTestReal->board) == -10)
    {
        if(finalTestReal->turn)
        {
            printf("Network Move:\n");
            std::vector<float> answer = TicTacToePlayer->feedForward(BoardToVec(finalTestReal->board, 27));
            int move = getMove(finalTestReal, answer);
            finalTestReal->move(move);
        }
        else
        {
            printf("Your Move:\n");
            int move;
            scanf("%d", &move);
            finalTestReal->move(move);
        }
        finalTestReal->displayBoard();
    }



}