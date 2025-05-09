#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
using namespace std;

float initWeightXavier(int fan_in, int fan_out) {
    float limit = sqrt(6.0f / (fan_in + fan_out));
    return ((static_cast<float>(rand()) / RAND_MAX) * 2 - 1) * limit;
}

float mse(vector<float> y_true, vector<float> y_pred) {
    size_t n = y_true.size();
    float error_sum = 0;

    for (int i=0; i<n; i++) {
        float error = y_true[i] - y_pred[i];
        error_sum += error*error;
    }

    return error_sum / n;
}

vector<float> msed(vector<float> y_true, vector<float> y_pred) {
    int n = y_true.size();
    vector<float> result(y_true.size());
    for (int i=0; i<n; i++) {
        result[i] = (2/n) * (y_pred[i] - y_true[i]);
    }
    return result;
}

struct NN {
    int inputSize;
    // weights[layer][neuron][input_index]
    vector<vector<vector<float>>> weights;
    // biases[layer][neuron]
    vector<vector<float>> biases;

    NN(int inputSize) : inputSize(inputSize) {}

    // Adds a layer with 'numNeurons' neurons.
    void addLayer(int numNeurons) {
        int fan_in = weights.empty() ? inputSize : weights.back().size();
        vector<vector<float>> layerWeights;
        vector<float> layerBiases;
        for (int i = 0; i < numNeurons; i++) {
            vector<float> neuronWeights;
            for (int j = 0; j < fan_in; j++) {
                neuronWeights.push_back(initWeightXavier(fan_in, numNeurons));
            }
            layerWeights.push_back(neuronWeights);
            layerBiases.push_back(0.0f); // bias initialized to 0
        }
        weights.push_back(layerWeights);
        biases.push_back(layerBiases);
    }

    void train(float y_true, float y_pred) {
        float oErr = y_pred * (1-y_pred) * (y_true - y_pred);
        
    }

    // Forward propagation (linear output, no activation)
    vector<float> predict(const vector<float>& input) {
        vector<float> activation = input;
        for (size_t l = 0; l < weights.size(); l++) {
            vector<float> newActivation;
            // For each neuron in the current layer:
            for (size_t i = 0; i < weights[l].size(); i++) {
                float sum = 0;
                // Compute dot product of neuron's weights with activation from previous layer
                for (size_t j = 0; j < weights[l][i].size(); j++) {
                    sum += weights[l][i][j] * activation[j];
                }
                sum += biases[l][i];
                newActivation.push_back(sum);
            }
            activation = newActivation;
        }
        return activation;
    }
};

float input;
int main() {
    NN myNetwork(1);
    myNetwork.addLayer(2);
    myNetwork.addLayer(1);

    while(true) {
        cin>>input;
        vector<float> prediction = myNetwork.predict({input});
        cout << prediction[0] << endl;
    }
    return 0;
}
