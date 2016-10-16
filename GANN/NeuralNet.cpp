#include "NeuralNet.h"

using namespace std;

NeuralNet::NeuralNet(int layerCount_, int hiddenSize_, int inputSize_, int outputSize_) :
	layerCount{ layerCount_ },
	hiddenSize{ hiddenSize_ },
	inputSize{ inputSize_ },
	outputSize{ outputSize_ },
	rng{ dev() }{
	if (layerCount < 2)
		throw exception("Need at least 2 layers");
}


NeuralNet::~NeuralNet(){
	delete input;
}



void NeuralNet::CreateRandom(){
	vector<bitset<9>> layers;

	auto layer = CreateRandomLayer(inputSize, layerCount == 2 ? outputSize : hiddenSize);
	layers.insert(layers.begin(), layer.begin(), layer.end());

	for (int i = 1; i + 2 < layerCount; i++){
		auto layer = CreateRandomLayer(hiddenSize, hiddenSize);
		layers.insert(layers.end(), layer.begin(), layer.end());
	}
	layer = CreateRandomLayer(layerCount == 2 ? inputSize : hiddenSize, outputSize);
	layers.insert(layers.end(), layer.begin(), layer.end());
	CreateByEncoding(layers);
}

void NeuralNet::CreateByEncoding(vector<bitset<9>>& encoding){

	auto iter = encoding.begin();
	Layer* curr = nullptr;

	for (int i = 0; i + 1 < layerCount; i++){
		int srcSize = hiddenSize, destSize = hiddenSize;
		if (i == 0)
			srcSize = inputSize;
		if (i + 2 == layerCount)
			destSize = outputSize;

		vector<bitset<9>> layerEncoding(iter, iter + (srcSize * destSize));

		auto next = new Layer(srcSize, destSize, layerEncoding);
		if (input == nullptr){
			input = next;
		}
		else{
			curr->SetNext(next);
			next->SetPrev(curr);
		}
		iter += (srcSize * destSize);
		curr = next;
	}
	output = new Layer(outputSize);
	curr->SetNext(output);
	output->SetPrev(curr);
}

vector<double> NeuralNet::Simulate(std::vector<double>& inputValues){
	vector<double> out;

	input->ClearNodeSums();
	input->Simulate(inputValues);
	return static_cast<const vector<double>>(output->GetNodeValues());
}

vector<bitset<9>> NeuralNet::Encode() const{
	vector<bitset<9>> bits;

	for (auto layer = input; layer->GetNext() != nullptr; layer = layer->GetNext()){
		auto layerEncoding = layer->Encode();
		bits.insert(bits.end(), layerEncoding.begin(), layerEncoding.end());	//TODO maybe make with move
	}
	return bits;
}


vector<bitset<9>> NeuralNet::CreateRandomLayer(int srcSize, int destSize){
	vector<bitset<9>> connections;

	for (int i = 0; i < srcSize * destSize; i++){
		bitset<9> connection((rng() % 256) - 128);
		connection.set(8, true);
		connections.push_back(connection);
	}
	return connections;
}