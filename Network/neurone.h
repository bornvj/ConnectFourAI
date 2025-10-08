#pragma once
#include <vector>

class Neurone
{
    public:
        std::vector<Neurone*> prev;
        std::vector<float> weights;
        float bias;
        float value;
    
        Neurone();
        Neurone(Neurone* n);

        void connect(Neurone* prev);
        float compute();
        float getOutput();
};
