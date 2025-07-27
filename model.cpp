// model.cpp
#include "model.h"
#include <cmath>
#include <iostream>

// Center-focused model with Gaussian weighting
double mock_model(const std::vector<std::vector<double>>& image) {
    double sum = 0.0;
    int height = (int)image.size();
    int width = (int)image[0].size();

    // Center coordinates
    double center_x = width / 2.0;
    double center_y = height / 2.0;
    
    // Gaussian parameters - adjust sigma to control focus area
    double sigma_x = width * 0.25;  // 25% of width for standard deviation
    double sigma_y = height * 0.25; // 25% of height for standard deviation
    
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // Distance from center
            double dx = x - center_x;
            double dy = y - center_y;
            
            // Gaussian weight - higher at center, lower at edges
            double weight = exp(-(dx*dx)/(2*sigma_x*sigma_x) - (dy*dy)/(2*sigma_y*sigma_y));
            
            sum += weight * image[y][x];
        }
    }
    return sum;
}

// Efficient batch gradient computation
std::vector<std::vector<double>> compute_all_gradients(
    const std::vector<std::vector<double>>& image, double epsilon) {
    
    int height = (int)image.size();
    int width = (int)image[0].size();
    
    std::vector<std::vector<double>> gradients(height, std::vector<double>(width, 0.0));
    
    // Center coordinates
    double center_x = width / 2.0;
    double center_y = height / 2.0;
    
    // Gaussian parameters
    double sigma_x = width * 0.25;
    double sigma_y = height * 0.25;
    
    // For this Gaussian model, we can compute gradients analytically
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            double dx = x - center_x;
            double dy = y - center_y;
            
            // Gaussian weight (this is the gradient for our linear weighted sum)
            double weight = exp(-(dx*dx)/(2*sigma_x*sigma_x) - (dy*dy)/(2*sigma_y*sigma_y));
            gradients[y][x] = weight;
        }
    }
    
    return gradients;
}

// Single pixel gradient for compatibility
double numeric_gradient(const std::vector<std::vector<double>>& image, int y, int x, double epsilon) {
    int height = (int)image.size();
    int width = (int)image[0].size();
    
    // Center coordinates
    double center_x = width / 2.0;
    double center_y = height / 2.0;
    
    // Gaussian parameters
    double sigma_x = width * 0.25;
    double sigma_y = height * 0.25;
    
    double dx = x - center_x;
    double dy = y - center_y;
    
    // Return the Gaussian weight directly (analytical gradient)
    return exp(-(dx*dx)/(2*sigma_x*sigma_x) - (dy*dy)/(2*sigma_y*sigma_y));
}