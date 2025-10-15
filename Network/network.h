#pragma once

#include <vector>
#include <nlohmann/json.hpp>

#include "../Game/board.h"
#include "neurone.h"
#include "layer.h"

class Network 
{ 
    public:
        Layer inputLayer;
        Layer hiddenLayer1;
        Layer hiddenLayer2;
        Layer outputLayer;
        long victories;
        long gamesPlayed;

        Network();
        Network(const Network& n);
        Network(const std::string& filename);
        Network& operator=(const Network& n);

        void save(const std::string& filename);

        int FeedForward(Board& board, Color iaColor);

        float getWinRate();

        void print();
};

namespace NetworkOperation
{
    Network Mutate(const Network& Network);
    Network Crossover(const Network& n1, const Network& n2);
}