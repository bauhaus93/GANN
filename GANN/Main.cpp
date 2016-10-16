#include <iostream>
#include <vector>

#include "NeuralNet.h"
#include "Tests.h"

using namespace std;

static void PrintVector(vector<double>& vec, string title);

extern bool RunTests(void);


int main(int argc, char **argv){
	RunTests();

	/*NeuralNet n(4, 4, 2, 1);
	vector<double> input{ 1.2, 2.3 };
	vector<double> output;


	n.CreateRandom();
	output = n.Simulate(input);

	PrintVector(input, "input: ");
	PrintVector(output, "output: ");*/


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