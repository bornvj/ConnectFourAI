#include "network.h"
#include "networkControl.h"
#include <cmath>

static float Activation(float value)
{
    return std::tanh(value);
}

static void FeedForwardOne(Layer& prevLayer, Layer& currentLayer)
{
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