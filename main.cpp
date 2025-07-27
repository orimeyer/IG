// main.cpp
#include <iostream>
#include "image_loader.h"
#include "grayscale_utils.h"
#include "model.h"
#include "ig.h"
#include "pgm_writer.h"
#include "stb_image.h"

// Simple bilinear resize function
std::vector<std::vector<double>> resize_image(const std::vector<std::vector<double>>& input, 
                                             int new_width, int new_height) {
    int old_height = input.size();
    int old_width = input[0].size();
    
    std::vector<std::vector<double>> resized(new_height, std::vector<double>(new_width));
    
    double x_ratio = static_cast<double>(old_width) / new_width;
    double y_ratio = static_cast<double>(old_height) / new_height;
    
    for (int y = 0; y < new_height; y++) {
        for (int x = 0; x < new_width; x++) {
            double orig_x = x * x_ratio;
            double orig_y = y * y_ratio;
            
            int x1 = static_cast<int>(orig_x);
            int y1 = static_cast<int>(orig_y);
            int x2 = std::min(x1 + 1, old_width - 1);
            int y2 = std::min(y1 + 1, old_height - 1);
            
            double dx = orig_x - x1;
            double dy = orig_y - y1;
            
            // Bilinear interpolation
            double val = input[y1][x1] * (1 - dx) * (1 - dy) +
                        input[y1][x2] * dx * (1 - dy) +
                        input[y2][x1] * (1 - dx) * dy +
                        input[y2][x2] * dx * dy;
            
            resized[y][x] = val;
        }
    }
    return resized;
}

int main() {
    const std::string input_filename = "C:/IG/assets/input.jpg";
    const std::string output_filename = "C:/IG/assets/output.pgm";

    int width, height, channels;
    unsigned char* image_data = load_image(input_filename.c_str(), width, height, channels);
    if (!image_data) {
        std::cerr << "Failed to load image: " << input_filename << std::endl;
        return 1;
    }

    std::cout << "Original image: " << width << "x" << height << " with " << channels << " channels" << std::endl;

    // Convert to grayscale
    auto input_gray = rgb_to_grayscale(image_data, width, height, channels);
    stbi_image_free(image_data);

    // Resize to smaller dimensions for faster computation (e.g., 256x256 max)
    int target_size = 128; // Start small for testing
    int new_width, new_height;
    
    if (width > height) {
        new_width = target_size;
        new_height = static_cast<int>((static_cast<double>(height) / width) * target_size);
    } else {
        new_height = target_size;
        new_width = static_cast<int>((static_cast<double>(width) / height) * target_size);
    }
    
    std::cout << "Resizing to: " << new_width << "x" << new_height << std::endl;
    auto resized_input = resize_image(input_gray, new_width, new_height);

    // baseline - black image
    std::vector<std::vector<double>> baseline(new_height, std::vector<double>(new_width, 0.0));

    // Compute IG with fewer steps for testing
    std::cout << "Computing Integrated Gradients..." << std::endl;
    int steps = 10; // Reduced from 50 for faster computation
    auto attributions = compute_ig(resized_input, baseline, steps);

    // Save result
    if (!save_pgm(output_filename, attributions)) {
        std::cerr << "Failed to save output image: " << output_filename << std::endl;
        return 1;
    }

    std::cout << "Integrated Gradients heatmap saved to: " << output_filename << std::endl;
    std::cout << "Note: Image was resized to " << new_width << "x" << new_height << " for faster computation" << std::endl;
    return 0;
}