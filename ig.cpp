// ig.cpp
#include "ig.h"
#include "model.h"

#include <vector>

std::vector<std::vector<double>> compute_ig(
    const std::vector<std::vector<double>>& input,
    const std::vector<std::vector<double>>& baseline,
    int steps) {

    int height = (int)input.size();
    int width = (int)input[0].size();

    
    std::vector<std::vector<double>> total_gradients(height, std::vector<double>(width, 0.0));

    for (int step = 1; step <= steps; ++step) {
        double alpha = static_cast<double>(step) / steps;

        
        std::vector<std::vector<double>> x_alpha(height, std::vector<double>(width, 0.0));
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                x_alpha[y][x] = baseline[y][x] + alpha * (input[y][x] - baseline[y][x]);
            }
        }

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                double grad = numeric_gradient(x_alpha, y, x, 1e-3);
                total_gradients[y][x] += grad;
            }
        }
    }

    // IG_i = (input_i - baseline_i) * (1/steps) * sum_gradients
    std::vector<std::vector<double>> attributions(height, std::vector<double>(width, 0.0));
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            attributions[y][x] = (input[y][x] - baseline[y][x]) * (total_gradients[y][x] / steps);
        }
    }

    return attributions;
}
