#include "Tests.h"

using namespace std;

static int TestIdempotence(int layerCount, int layerSize);
static int TestCreateLayerCountOne(void);

bool RunTests(void){
	int failed = 0;

	cout << "run tests..." << endl;

	if (TestCreateLayerCountOne() != 0)
		failed++;

	cout << "test idempotence..." << endl;
	for (int i = 2; i < 10; i++){
		for (int j = 1; j < 10; j++){
			if (TestIdempotence(i, j) != 0)
				failed++;
		}
	}


	if (failed > 0){
		cout << failed << " tests failed" << endl;
	}
	else
		cout << "all tests sucessful" << endl;
	return failed == 0;
}

static int TestCreateLayerCountOne(void){
	cout << "test layer count one creation..." << endl;

	try{
		NeuralNet n(1, 4);
		cout << "no exception thrown with layer count one!" << endl;
		return 1;

	}
	catch (exception& e){
		//cout << "caught exception: " << e.what() << endl;
	}
	return 0;
}


static int TestIdempotence(int layerCount, int layerSize){
	NeuralNet n(layerCount, layerSize);
	NeuralNet n2(layerCount, layerSize);
	vector<double> input{ 1.2, 2.3 };
	int mismatches = 0;

	n.CreateRandom();

	auto encode = n.Encode();
	auto encode2 = n2.Encode();

	if (encode.size() != encode2.size()){
		cout << "encoding sizes do not match: " << encode.size() << "/" << encode2.size() << endl;
		return -1;
	}
	else{
		for (int i = 0; i < encode.size(); i++){
			if (encode.at(i) != encode2.at(i)){
				cout << "mismatch at row " << i << ": " << encode.at(i) << " / " << encode2.at(i) << endl;
				mismatches++;
			}

		}
	}
	return mismatches;
}

