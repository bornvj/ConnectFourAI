#pragma once
#include <vector>
#include <nlohmann/json.hpp>

class Layer
{
    public:
        std::vector<std::vector <float>> weights;
        std::vector<float> bias;
        std::vector<float> values;

        Layer() = default;
        Layer(int prevLayerSize, int layerSize);
        Layer(const Layer& layer);
        Layer(const nlohmann::json& j);

        Layer& operator=(const Layer& other);

        nlohmann::json to_json();
};