// grayscale_utils.h
#ifndef GRAYSCALE_UTILS_H
#define GRAYSCALE_UTILS_H

#include <vector>

std::vector<std::vector<double>> rgb_to_grayscale(const unsigned char* rgb_data, int width, int height, int channels);

#endif // GRAYSCALE_UTILS_H
