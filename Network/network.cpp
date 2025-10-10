#include <cmath>
#include <cassert>

#include "network.h"
#include "networkControl.h"


static float Activation(float value)
{
    return std::tanh(value);
}

static void FeedForwardOne(Layer& prevLayer, Layer& currentLayer)
{
    assert(prevLayer.values.size() == currentLayer.weights[0].size());

    for (size_t neuroneIndex = 0; neuroneIndex < currentLayer.values.size(); neuroneIndex++)
    {
        currentLayer.values[neuroneIndex] = 0.0f;
        for (size_t prevNeuroneIndex = 0; prevNeuroneIndex < prevLayer.values.size(); prevNeuroneIndex++)
            currentLayer.values[neuroneIndex] += currentLayer.weights[neuroneIndex][prevNeuroneIndex] * prevLayer.values[prevNeuroneIndex];

        currentLayer.values[neuroneIndex] += currentLayer.bias[neuroneIndex];
        currentLayer.values[neuroneIndex] = Activation(currentLayer.values[neuroneIndex]);
    }
}

Network::Network() : inputLayer(0, INPUTLAYERSIZE),
    hiddenLayer1(INPUTLAYERSIZE, HIDDENLAYER1SIZE),
    hiddenLayer2(HIDDENLAYER1SIZE, HIDDENLAYER2SIZE),
    outputLayer(HIDDENLAYER2SIZE, OUTPUTLAYERSIZE)
{
    victories = 0;
}

Network::Network(const Network& n) : 
    inputLayer(Layer(n.inputLayer)),
    hiddenLayer1(Layer(n.hiddenLayer1)),
    hiddenLayer2(Layer(n.hiddenLayer2)),
    outputLayer(Layer(n.outputLayer)),
    victories(n.victories)
{
}

Network& Network::operator=(const Network& n)
{
    if (this != &n) {
        inputLayer = n.inputLayer;
        hiddenLayer1 = n.hiddenLayer1;
        hiddenLayer2 = n.hiddenLayer2;
        outputLayer = n.outputLayer;
        victories = n.victories;
    }
    return *this;
}

int Network::FeedForward(Board& board, Color iaColor)
{
    int index = 0;

    // Feed input values
    for (int row = 0; row < NB_ROW; row++)
    {    
        for (int col = 0; col < NB_COL; col++, index++)
        {
            Color c = board.getSquare(row, col);

            if (c == EMPTY)
                inputLayer.values[index] = 0.0f;
            else
                inputLayer.values[index] = (c == iaColor) ? 1.0f : -1.0f;
        }
    }

    if (DEBBUG)
    {
    std::cout << "inputLayer: values=" << inputLayer.values.size() << std::endl;
    std::cout << "hiddenLayer1: values=" << hiddenLayer1.values.size() 
            << ", weights[0]=" << hiddenLayer1.weights[0].size() << std::endl;
    std::cout << "hiddenLayer2: values=" << hiddenLayer2.values.size() 
            << ", weights[0]=" << hiddenLayer2.weights[0].size() << std::endl;
    std::cout << "outputLayer: values=" << outputLayer.values.size() 
            << ", weights[0]=" << outputLayer.weights[0].size() << std::endl << std::endl;
    }

    FeedForwardOne(inputLayer, hiddenLayer1);
    FeedForwardOne(hiddenLayer1, hiddenLayer2);
    FeedForwardOne(hiddenLayer2, outputLayer);


    float maxValue = outputLayer.values[0];
    int selectedColumn = 0;

    for (int i = 1; i < OUTPUTLAYERSIZE; i++)
    {
        if (outputLayer.values[i] > maxValue)
        {
            maxValue = outputLayer.values[i];
            selectedColumn = i;
        }
    }

    return selectedColumn;
}