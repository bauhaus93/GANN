#include <iostream>
#include <vector>


#include "NeuralNet.h"
#include "Genetic.h"
#include "Tests.h"

using namespace std;

static void PrintVector(vector<double>& vec, string title);

extern bool RunTests(void);
extern double BoolVectorToDouble(std::vector<bool>& vec, int from, int to);
extern std::vector<bool> DoubleToBoolVector(double value);


int main(int argc, char **argv){

	NeuralNet nn(4, 4);
	nn.CreateRandom();

	cout << nn << endl;

	return 0;
}



static void PrintVector(vector<double>& vec, string title){
	cout << title;
	for (int i = 0; i < vec.size(); i++){
		cout << vec[i];
		if (i + 1 == vec.size())
			cout << endl;
		else
			cout << "/";
	}
}