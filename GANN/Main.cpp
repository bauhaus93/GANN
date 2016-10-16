#include <iostream>
#include <vector>

#include "NeuralNet.h"
#include "Genetic.h"
#include "Tests.h"

using namespace std;

static void PrintVector(vector<double>& vec, string title);

extern bool RunTests(void);


int main(int argc, char **argv){
	RunTests();

	Genetic g(16, 0.1);
	g.Run(1000);

	auto code = g.GetFittest();

	NeuralNet n(4, 4);
	vector<double> input{ 3, 7, 0, 0 }, output;

	n.CreateByEncoding(code);
	for (int i = 0; i < 10; i++){
		for (int j = 0; j < 10; j++){
			input.at(0) = i;
			input.at(1) = j;
			output = n.Simulate(input);
			cout << i << " * " << j << " = " << output.at(0) << endl;
		}
	}
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