#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>  
#include "colors.h"
#include "board.h"
#include "Network/network.h"
#include "trainer.h"
using namespace std;


int main(int argc, char *argv[]) 
{
    if (argc != 2)
    {
        std::cout << "program needs parameters" << std::endl;
        return 1;
    }

    if (strcmp(argv[1], "train") == 0)
    {
        srand(time(nullptr));
    
        Network best = trainer::train();

        best.save("bestTest.json");
    }
    if (strcmp(argv[0], "play") == 0)
    {
        Network AI = Network("BestTest.json");
        while (true)
        {
            Board b = Board();
            int choice;

            while (!b.IsFull() && !b.IsFinished())
            {
                b.MakeMove(AI.FeedForward(b, YELLOW), YELLOW);
                b.Print();
                std::cin >> choice;
                b.MakeMove(choice, RED);
                b.Print();
            }
        }
    }
    return 1;
}