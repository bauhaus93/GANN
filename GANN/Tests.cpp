#include "Tests.h"

using namespace std;
static int TestIdempotence(int layerCount, int layerSize);
static int TestCreateLayerCountOne(void);
static int TestLayerSizeZero(void);
static void MeasureEncodingTime(int count, int size);
static void MeasureDecodingTime(int count, int size);

bool RunTests(void){
	int failed = 0;

	cout << "run tests..." << endl;

	if (TestCreateLayerCountOne() != 0)
		failed++;

	if (TestLayerSizeZero() != 0)
		failed++;

	cout << "test idempotence..." << endl;
	for (int i = 2; i < 5; i++){
		for (int j = 1; j < 5; j++){
			if (TestIdempotence(i, j) != 0)
				failed++;
		}
	}


	if (failed > 0){
		cout << failed << " tests failed" << endl;
	}
	else
		cout << "all tests sucessful" << endl;

	if (failed == 0){
		MeasureEncodingTime(4, 4);
		MeasureDecodingTime(4, 4);
	}

	return failed == 0;
}

int TestCreateLayerCountOne(void){
	cout << "test layer count one creation..." << endl;

	try{
		NeuralNet n(1, 4);
		cout << "no exception thrown with layer count one!" << endl;
		return 1;

	}
	catch (exception& e){
		cout << "caught exception: " << e.what() << endl;
	}
	return 0;
}

int TestLayerSizeZero(void){
	cout << "test layer size zero..." << endl;

	try{
		NeuralNet n(1, 4);
		cout << "no exception thrown with layer size zero!" << endl;
		return 1;

	}
	catch (exception& e){
		cout << "caught exception: " << e.what() << endl;
	}
	return 0;
}

int TestIdempotence(int layerCount, int layerSize){
	NeuralNet n(layerCount, layerSize);
	NeuralNet n2(layerCount, layerSize);
	int mismatches = 0;

	cout << "test idempotence with layercount = " << layerCount << ", layersize = " << layerSize << "..." << endl;

	n.CreateRandom();
	auto encode = n.Encode();


	n2.Decode(encode);
	auto encode2 = n2.Encode();

	if (encode.size() != encode2.size()){
		cout << "encoding sizes do not match: " << encode.size() << "/" << encode2.size() << endl;
		return -1;
	}
	else{
		for (size_t i = 0; i < encode.size(); i++){
			if (encode.at(i) != encode2.at(i)){
				cout << "mismatch at row " << i << ": " << encode.at(i) << " / " << encode2.at(i) << endl;
				mismatches++;
			}

		}
	}
	return mismatches;
}

void MeasureEncodingTime(int count, int size){
	NeuralNet n(count, size);

	n.CreateRandom();

	auto start = chrono::high_resolution_clock::now();
	n.Encode();
	auto diff = chrono::high_resolution_clock::now() - start;

	cout << "encoding time of " << count << "x" << size << ": " << int(diff.count() * 1e3 * chrono::high_resolution_clock::time_point::period().num / chrono::high_resolution_clock::time_point::period().den) << "ms" << endl;
}

void MeasureDecodingTime(int count, int size){
	NeuralNet n(count, size);
	NeuralNet n2(count, size);

	n.CreateRandom();
	auto encoding = n.Encode();

	auto start = chrono::high_resolution_clock::now();
	n.Decode(encoding);
	auto diff = chrono::high_resolution_clock::now() - start;

	cout << "decoding time of " << count << "x" << size << ": " << int(diff.count() * 1e3 * chrono::high_resolution_clock::time_point::period().num / chrono::high_resolution_clock::time_point::period().den) << "ms" << endl;
}
