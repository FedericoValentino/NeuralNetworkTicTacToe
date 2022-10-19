#include <cstdio>
#include <vector>
#include <iterator>
#include <algorithm>
#include "TicTacToe/TicTacToe.h"
#include "BrainLib/BrainFart.h"

#define GENERATIONS 100

#define TESTINDIVIDUALS 100


struct individual
{
    BrainFart* CPU;
    int fitness;
};

typedef struct individual Individual;

bool comp(Individual* i1, Individual* i2)
{
    return i1->fitness > i2->fitness;
}

int max(const float* array, int size, TicTacToe* game)
{
    float max = 0;
    int returnValue = 0;
    for(int i = 0; i < size; i++)
    {
        if(array[i] > max)
        {
            if(game->isMoveAvailable(i))
            {
                max = array[i];
                returnValue = i;
            }
        }
    }

    delete array;
    return returnValue;
}

void playGame(Individual* BestPlayer)
{
    TicTacToe* currentGame = new TicTacToe();

    while(!currentGame->isGameDone())
    {
        std::vector<float> input;
        for(int k = 0; k < 9; k++)
        {
            input.push_back((float)currentGame->getBoard()[k]);
        }
        int networkGuess;

        networkGuess = max(BestPlayer->CPU->feedForward(input), 9, currentGame);

        printf("Machine move is %d\n", networkGuess);
        currentGame->move(networkGuess);

        currentGame->displayBoard();

        printf("Play your move\n");
        int playerMove = 0;
        scanf("%d", &playerMove);

        currentGame->move(playerMove);

        currentGame->displayBoard();

    }
    delete currentGame;
}

void startGame(Individual* currentSubject, Individual* currentFoe)
{
    TicTacToe* currentGame = new TicTacToe();

    while(!currentGame->isGameDone())
    {
        std::vector<float> input;
        for(int k = 0; k < 9; k++)
        {
            input.push_back((float)currentGame->getBoard()[k]);
        }
        int guess;
        if(currentGame->getTurn())
        {
            guess = max(currentSubject->CPU->feedForward(input), 9, currentGame);
        }
        else
        {
            guess = max(currentFoe->CPU->feedForward(input), 9, currentGame);
        }
        printf("move is %d\n", guess);
        currentGame->move(guess);
        currentGame->displayBoard();
    }
    delete currentGame;
}

int main()
{

    printf("TicTacToe\n");
    std::vector<Individual*> testSubjects;

    for(int i = 0; i < TESTINDIVIDUALS; i++)
    {
        Individual* subject = new Individual;
        subject->CPU = new BrainFart({9, 18, 18, 9});
        subject->fitness = 0;
        testSubjects.push_back(subject);
    }

    printf("Training...\n");
    for(int generation = 0; generation < GENERATIONS; generation++)
    {
        for(int j = 0; j < TESTINDIVIDUALS; j++)
        {
            Individual* currentSubject = testSubjects[j];
            currentSubject->fitness = 0;
            for(int foe = 0; foe < TESTINDIVIDUALS; foe++)
            {
                Individual* currentFoe = testSubjects[foe];

                TicTacToe* currentGame = new TicTacToe();

                while(!currentGame->isGameDone())
                {
                    std::vector<float> input;
                    for(int l = 0; l < 9; l++)
                    {
                        input.push_back((float)currentGame->getBoard()[l]);
                    }
                    int guess;
                    if(currentGame->getTurn())
                    {
                        guess = max(currentSubject->CPU->feedForward(input), 9, currentGame);
                    }
                    else
                    {
                        guess = max(currentFoe->CPU->feedForward(input), 9, currentGame);
                    }
                    currentGame->move(guess);
                }

                currentSubject->fitness += currentGame->getP1Reward();
                delete currentGame;
            }
        }

        std::sort(testSubjects.begin(), testSubjects.end(), comp);

        printf("The best individual had fitness: %d\n", testSubjects[0]->fitness);

        Individual* father = testSubjects[0];


        startGame(father, father);


        std::vector<Individual*> newGeneration;
        newGeneration.clear();

        for(int session = 0; session < 10; session++)
        {
            for(int partner = 1; partner <= 10; partner++)
            {
                Individual* son = new Individual;
                son->CPU = BrainFart::reproduce(father->CPU, testSubjects[partner]->CPU);
                //son->CPU = BrainFart::cloneBrain(father->CPU);
                son->fitness = 0;
                son->CPU->mutate();
                newGeneration.push_back(son);
            }
        }

        for(int k = 0; k < TESTINDIVIDUALS; k++)
        {
            testSubjects[k]->CPU->freeBrain();
            delete testSubjects[k]->CPU;
            delete testSubjects[k];
        }

        testSubjects.clear();

        testSubjects = newGeneration;

    }


    printf("Ready to play!\n");

    playGame(testSubjects[0]);


    for(int i = 0; i < TESTINDIVIDUALS; i++)
    {
        testSubjects[i]->CPU->freeBrain();
        delete testSubjects[i]->CPU;
        delete testSubjects[i];
    }

}