// model.h
#ifndef MODEL_H
#define MODEL_H

#include <vector>

double mock_model(const std::vector<std::vector<double>>& image);

double numeric_gradient(const std::vector<std::vector<double>>& image, int y, int x, double epsilon);

#endif // MODEL_H
