#include <cmath>
#include "neurone.h"

Neurone::Neurone()
{
    bias = ((float)rand() / RAND_MAX) * 2 - 1;
    value = 0.0f;
}

Neurone::Neurone(Neurone* n)
{
    for (long unsigned int i = 0; i < prev.size(); i++)
            this->weights.push_back(n->weights[i]);

    bias = n->bias;
}

void Neurone::connect(Neurone* prev)
{
    this->prev.push_back(prev);
    weights.push_back(((float)rand() / RAND_MAX) * 2 - 1);
}

float Neurone::compute()
{
    value = 0;
    for (long unsigned int i = 0; i < prev.size(); i++)
        value += prev[i]->getOutput() * weights[i];
    
    value += bias;

    value = std::tanh(value);
    return value; 
}

float Neurone::getOutput()
{
    return value;
}