#include <iostream>
#include <vector>

#include "NeuralNet.h"

using namespace std;

static void PrintVector(vector<double>& vec, string title);
static void TestIdempotence(void);


int main(int argc, char **argv){
	/*NeuralNet n(4, 4, 2, 1);
	vector<double> input{ 1.2, 2.3 };
	vector<double> output;


	n.CreateRandom();
	output = n.Simulate(input);

	PrintVector(input, "input: ");
	PrintVector(output, "output: ");*/

	TestIdempotence();




	return 0;
}

static void TestIdempotence(void){
	NeuralNet n(4, 4, 2, 1);
	NeuralNet n2(4, 4, 2, 1);
	vector<double> input{ 1.2, 2.3 };

	cout << "test idempotence:" << endl;

	n.CreateRandom();
	n2.CreateByEncoding(n.Encode());

	auto encode = n.Encode();
	auto encode2 = n2.Encode();

	if (encode.size() != encode2.size()){
		cout << "encoding sizes do not match: " << encode.size() << "/" << encode2.size() << endl;
	}
	else{
		for (int i = 0; i < encode.size(); i++){
			if (encode.at(i) != encode2.at(i)){
				cout << "mismatch at row " << i << ": " << encode.at(i) << " / " << encode2.at(i) << endl;
			}
		}
	}
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