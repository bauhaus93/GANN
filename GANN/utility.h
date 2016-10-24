#pragma once

#include <vector>

extern std::vector<bool> DoubleToBoolVector(double value);
extern double BoolVectorToDouble(std::vector<bool>& vec, int start);