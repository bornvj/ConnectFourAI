#pragma once
#include <vector>
#include "network.h"

class Layer
{
    public:
        std::vector<std::vector <float>> weights;
        std::vector<float> bias;
        std::vector<float> values;

        Layer(int prevLayerSize, int layerSize)
        {
            values.resize(layerSize);
            if (prevLayerSize == 0)
            {
                weights.resize(0);
                bias.resize(0);
                return;
            }
            
            weights.resize(layerSize);
            bias.resize(layerSize);

            for (int i = 0; i < layerSize; i++)
            {
                weights[i].resize(prevLayerSize);
                for (int j = 0; j < prevLayerSize; j++)
                    weights[i][j] = ((float)rand() / RAND_MAX) * 2 - 1;

                bias[i] = ((float)rand() / RAND_MAX) * 2 - 1;
                values[i] = 0.0f;
            }
        } 
};