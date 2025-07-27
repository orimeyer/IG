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

    // 2D מערך לאגרגציה של הגרדיאנטים לאורך הצעדים
    std::vector<std::vector<double>> total_gradients(height, std::vector<double>(width, 0.0));

    for (int step = 1; step <= steps; ++step) {
        double alpha = static_cast<double>(step) / steps;

        // חשב נקודת אינטרפולציה x_alpha = baseline + alpha * (input - baseline)
        std::vector<std::vector<double>> x_alpha(height, std::vector<double>(width, 0.0));
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                x_alpha[y][x] = baseline[y][x] + alpha * (input[y][x] - baseline[y][x]);
            }
        }

        // חשב גרדיאנט נומרי עבור כל פיקסל ב-x_alpha
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                double grad = numeric_gradient(x_alpha, y, x);
                total_gradients[y][x] += grad;
            }
        }
    }

    // ממיר סכום גרדיאנטים לאטtributions לפי הנוסחה:
    // IG_i = (input_i - baseline_i) * (1/steps) * sum_gradients
    std::vector<std::vector<double>> attributions(height, std::vector<double>(width, 0.0));
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            attributions[y][x] = (input[y][x] - baseline[y][x]) * (total_gradients[y][x] / steps);
        }
    }

    return attributions;
}
