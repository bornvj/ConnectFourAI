#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>  
#include "colors.h"
#include "board.h"
#include "network.h"
#include "trainer.h"
using namespace std;


int main() 
{
    srand(time(nullptr));

    Network best = trainer::train();

    while (true)
    {
        Board b = Board();
        int choice;

        while (!b.IsFull() && !b.IsFinished())
        {
            b.MakeMove(best.FeedForward(b, YELLOW), YELLOW);
            b.Print();
            std::cin >> choice;
            b.MakeMove(choice, RED);
            b.Print();
        }
    }
}