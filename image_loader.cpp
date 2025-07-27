// image_loader.cpp
#include "image_loader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

unsigned char* load_image(const char* filename, int& width, int& height, int& channels) {
    unsigned char* data = stbi_load(filename, &width, &height, &channels, 0);
    return data;
}
