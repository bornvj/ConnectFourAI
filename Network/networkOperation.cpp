#include "network.h"
#include "networkControl.h"

bool ShouldMutate(float mutateProb) // return if the number in [0; 1] < mutateProb
{
    return (rand() / (float)RAND_MAX) < mutateProb;
}

float randInDelta(float delta) // generate a rand in [-delta; delta]
{
    return ((rand() / (float)RAND_MAX) * 2.0f - 1.0f) * delta;
}

void mutateLayer(Layer& layer)
{
    for (size_t i = 0; i < layer.weights.size(); i++)
        for (size_t j = 0; j < layer.weights[i].size(); j++)
            if (ShouldMutate(MUTATEPROB))
                layer.weights[i][j] += randInDelta(MUTATEDELTA);

    for (size_t i = 0; i < layer.bias.size(); i++)
        layer.bias[i] += ShouldMutate(MUTATEPROB)? randInDelta(MUTATEDELTA) :0;
}

void crossoverLayer(Layer& newLayer, const Layer& l1, const Layer& l2)
{
    for (size_t i = 0; i < newLayer.weights.size(); i++)
        for (size_t j = 0; j < newLayer.weights[i].size(); j++)
           newLayer.weights[i][j] = ((rand() / (float)RAND_MAX) < 0.5f)? l1.weights[i][j] : l2.weights[i][j];

    for (size_t i = 0; i < newLayer.bias.size(); i++)
        newLayer.bias[i] = ((rand() / (float)RAND_MAX) < 0.5f)? l1.bias[i] : l2.bias[i];
}


Network NetworkOperation::Mutate(const Network& network)
{
    Network newNetwork = Network(network);

    mutateLayer(newNetwork.hiddenLayer1);
    mutateLayer(newNetwork.hiddenLayer2);
    mutateLayer(newNetwork.outputLayer);

    return newNetwork;
}

Network NetworkOperation::Crossover(const Network& n1, const Network& n2)
{
    Network newNetwork = Network(n1);

    crossoverLayer(newNetwork.hiddenLayer1, n1.hiddenLayer1, n2.hiddenLayer1);
    crossoverLayer(newNetwork.hiddenLayer2, n1.hiddenLayer2, n2.hiddenLayer2);
    crossoverLayer(newNetwork.outputLayer, n1.outputLayer, n2.outputLayer);

    return newNetwork;
}