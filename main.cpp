#include <cstdio>
#include <vector>
#include <iterator>
#include "TicTacToe/TicTacToe.h"
#include "BrainLib/BrainFart.h"

#define GENERATIONS 200

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

int max(const float* array, int size)
{
    float max = 0;
    int returnValue;
    for(int i = 0; i < size; i++)
    {
        if(array[i] > max)
        {
            max = array[i];
            returnValue = i;
        }
    }
    return returnValue;
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
            guess = max(currentSubject->CPU->feedForward(input), 9);
        }
        else
        {
            guess = max(currentFoe->CPU->feedForward(input), 9);
        }
        currentGame->move(guess);
        currentGame->displayBoard();
    }
    free(currentGame);
}

int main()
{
    std::vector<Individual*> testSubjects;

    for(int i = 0; i < TESTINDIVIDUALS; i++)
    {
        Individual* subject = new Individual;
        subject->CPU = new BrainFart({9, 10, 10, 9});
        subject->fitness = 0;
        testSubjects.push_back(subject);
    }


    for(int i = 0; i < GENERATIONS; i++)
    {
        for(int i = 0; i < TESTINDIVIDUALS; i++)
        {
            Individual* currentSubject = testSubjects[i];
            currentSubject->fitness = 0;
            for(int j = 0; j < TESTINDIVIDUALS; j++)
            {
                Individual* currentFoe = testSubjects[j];

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
                        guess = max(currentSubject->CPU->feedForward(input), 9);
                    }
                    else
                    {
                        guess = max(currentFoe->CPU->feedForward(input), 9);
                    }
                    currentGame->move(guess);
                }

                currentSubject->fitness += currentGame->getP1Reward();
                free(currentGame);
            }
            //printf("Subject: %d\tFitness:%d\n", i+1, currentSubject->fitness);
        }

        std::sort(testSubjects.begin(), testSubjects.end(), comp);

        printf("The best 2 were:\n fitness: %d, fitness: %d\n", testSubjects[0]->fitness, testSubjects[1]->fitness);

        Individual* father = testSubjects[0];
        Individual* mother = testSubjects[1];


        startGame(father, mother);

        for(int i = 2; i < TESTINDIVIDUALS; i++)
        {
            testSubjects[i]->CPU->freeBrain();
            free(testSubjects[i]->CPU);
            free(testSubjects[i]);
        }

        testSubjects.clear();

        for(int child = 0; child < 98; child++)
        {
            Individual* son = new Individual;
            son->CPU = BrainFart::reproduce(father->CPU, mother->CPU);
            son->fitness = 0;
            son->CPU->mutate();
            testSubjects.push_back(son);
        }

        testSubjects.push_back(father);
        testSubjects.push_back(mother);
    }

}