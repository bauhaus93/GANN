#pragma once

#include <vector>
#include <cstdint>

extern std::vector<bool> DoubleToBoolVector(double value);
extern double BoolVectorToDouble(std::vector<bool>& vec, int start);
