// pgm_writer.cpp
#include "pgm_writer.h"
#include "model.h"
#include <fstream>
#include <algorithm>

bool save_pgm(const std::string& filename, const std::vector<std::vector<double>>& data) {
    int height = (int)data.size();
    if (height == 0) return false;
    int width = (int)data[0].size();

    // מצא את המינימום והמקסימום במטריצה כדי לנרמל את הערכים 0-255
    double min_val = data[0][0];
    double max_val = data[0][0];
    for (const auto& row : data) {
        for (double v : row) {
            if (v < min_val) min_val = v;
            if (v > max_val) max_val = v;
        }
    }
    double range = max_val - min_val;
    if (range == 0) range = 1.0; // למנוע חלוקה באפס

    std::ofstream ofs(filename, std::ios::out | std::ios::binary);
    if (!ofs.is_open()) return false;

    // כותרת PGM בינארית P5
    ofs << "P5\n" << width << " " << height << "\n255\n";

    // כתיבת הפיקסלים אחרי נרמול
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // נרמל ל־0-255
            int pixel = static_cast<int>(255 * (data[y][x] - min_val) / range);
            if (pixel < 0) pixel = 0;
            else if (pixel > 255) pixel = 255;
            unsigned char c = static_cast<unsigned char>(pixel);
            ofs.write(reinterpret_cast<const char*>(&c), 1);
        }
    }
    ofs.close();
    return true;
}
