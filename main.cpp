#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime> 

#include "Game/board.h"
#include "Game/colors.h"
#include "Network/network.h"
#include "trainer.h"


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

        best.save("bestNetwork.ntw");

        return 0;
    }
    if (strcmp(argv[1], "play") == 0)
    {
        Network AI = Network("bestNetwork.ntw");
        std::cout << "netword Loaded!" << std::endl;

        AI.print();

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