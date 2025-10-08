#pragma once
#include <vector>
#include "neurone.h"
#include "board.h"
#include "layer.h"
#include "network.h"

class Network 
{ 
    public:
        Layer inputLayer;
        Layer hiddenLayer1;
        Layer hiddenLayer2;
        Layer outputLayer;
        long victories;

        Network();

        int FeedForward(Board& board, Color iaColor);
};

namespace NetworkOperation
{
    Network Mutate(const Network& Network);
    Network Crossover(const Network& n1, const Network& n2);
}