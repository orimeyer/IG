// model.h
#ifndef MODEL_H
#define MODEL_H

#include <vector>

double mock_model(const std::vector<std::vector<double>>& image);

double numeric_gradient(const std::vector<std::vector<double>>& image, int y, int x, double epsilon = 1e-3);

#endif // MODEL_H
