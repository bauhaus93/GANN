#include "Utility.h"

using namespace std;

vector<bool> DoubleToBoolVector(double value){
	union{ uint64_t u; double d; } converter;
	vector<bool> result;

	converter.d = value;

	while (result.size() < 8 * sizeof(double)){
		result.insert(result.begin(), (converter.u & 1));
		converter.u >>= 1;
	}

	return result;
}

double BoolVectorToDouble(vector<bool>& vec, int start){
	union{ uint64_t u; double d; } converter;
	int end = start + 8 * sizeof(double);
	converter.u = 0;

	for (int i = start; i < end; i++){
		converter.u |= vec.at(i);
		if (i + 1 < end)
			converter.u <<= 1;
	}
	return converter.d;
}
