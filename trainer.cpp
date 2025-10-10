#include "Network/networkControl.h"
#include "Network/network.h"
#include "board.h"
#include "trainer.h"
#include <algorithm>

Result fightNetworks(Network& n1, Network& n2)
{
    Board b = Board();
    
    while(!b.IsFinished() && !b.IsFull())
    {
        if (!b.MakeMove(n1.FeedForward(b, RED), RED))
            return SECONDWINNER; // disqualified
        if (!b.MakeMove(n2.FeedForward(b, YELLOW), YELLOW))
            return SECONDWINNER; // disqualified
    }

    switch (b.IsFinished())
    {
    case RED:
        return FIRSTWINNER;
        break;
    case YELLOW:
        return SECONDWINNER;
        break;
    default:
        return TIE;
        break;
    }
}

Network trainer::train()
{
    std::vector<Network> population(POPSIZE);

    for (size_t iter = 0; iter < NBRITERATIONS; iter++)
    {
       for (auto& n : population)
            n.victories = 0; // reset victories

        for (size_t i = 0; i < population.size(); i++)
        {
            for (size_t b = 0; b < NBRBATTLES; b++) 
            {
                size_t j;
                do { j = rand() % POPSIZE; } while (j == i); // éviter de jouer contre soi
                switch(fightNetworks(population[i], population[j])) 
                {
                    case FIRSTWINNER:  population[i].victories++; 
                    break;
                    case SECONDWINNER: population[j].victories++; 
                    break;
                    default: 
                    break;
                }
             }
        }

        std::sort(population.begin(), population.end(),
            [](const Network& a, const Network& b) {
            return a.victories > b.victories;
            });

        std::cout << iter << " itérations |";
        for (int i = 0; i < 10; i++)
            std::cout << population[i].victories << " | ";

        std::cout << std::endl;

        population.erase(population.begin() + (POPSIZE / 4), population.end()); // garde 1/4

        for (int i = 0; i < POPSIZE / 4; i++)
            population.push_back(NetworkOperation::Mutate(population[i]));
        // 2/4
        
        for (int i = 0; i < POPSIZE / 4; i++)
            population.push_back(NetworkOperation::Crossover(
                population[rand() % population.size()],
                population[rand() % population.size()]));
        // 3/4

        for (int i = 0; i < POPSIZE / 4; i++)
            population.push_back(NetworkOperation::Crossover(
                population[rand() % population.size()],
                population[rand() % population.size()]));
        // 4/4
    }
    return population[0];
}