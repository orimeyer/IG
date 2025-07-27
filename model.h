// model.h
#ifndef MODEL_H
#define MODEL_H

#include <vector>

// פונקציית מודל מדומה שמקבלת תמונה בגווני אפור ומחזירה סקלר (פלט)
double mock_model(const std::vector<std::vector<double>>& image);

// פונקציה שמחשבת גרדיאנט נומרי (לפי שינוי פיקסל אחד ב-epsilon)
double numeric_gradient(const std::vector<std::vector<double>>& image, int y, int x, double epsilon = 1e-3);

#endif // MODEL_H
