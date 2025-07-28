// grayscale_utils.cpp
#include "grayscale_utils.h"


std::vector<std::vector<double>> rgb_to_grayscale(const unsigned char* rgb_data, int width, int height, int channels) {
    std::vector<std::vector<double>> gray_image(height, std::vector<double>(width, 0.0));

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int idx = (y * width + x) * channels;
            double r = rgb_data[idx];
            double g = (channels > 1) ? rgb_data[idx + 1] : r;
            double b = (channels > 2) ? rgb_data[idx + 2] : r;

            
            double gray = 0.299 * r + 0.587 * g + 0.114 * b;
            gray_image[y][x] = gray;
        }
    }
    return gray_image;
}
