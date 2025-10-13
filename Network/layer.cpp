#include "layer.h"


Layer::Layer() = default;

Layer::Layer(int prevLayerSize, int layerSize)
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

Layer::Layer(const Layer& layer) :
    weights(layer.weights),
    bias(layer.bias),
    values(layer.values)
{
}

Layer::Layer(const nlohmann::json& j)
{            
    for (const nlohmann::json& weight : j.at("weights"))
        weights.push_back(weight.get<std::vector<float>>());

    bias = j.at("bias").get<std::vector<float>>();
}

Layer& Layer::operator=(const Layer& other) 
{
    if (this != &other) {
        weights = other.weights;
        bias = other.bias;
        values = other.values;
    }
    return *this;
}

nlohmann::json Layer::to_json()
{
    nlohmann::json ret;
    ret["weights"] = weights;
    ret["bias"] = bias;
    return ret;
}
};