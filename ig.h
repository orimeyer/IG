// ig.h
#ifndef IG_H
#define IG_H

#include <vector>

std::vector<std::vector<double>> compute_ig(
    const std::vector<std::vector<double>>& input,
    const std::vector<std::vector<double>>& baseline,
    int steps = 50);

#endif // IG_H
