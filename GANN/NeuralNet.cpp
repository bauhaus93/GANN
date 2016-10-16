#include "NeuralNet.h"

using namespace std;

NeuralNet::NeuralNet(int layerCount_, int layerSize_) :
	input{ nullptr },
	output{ nullptr },
	layerCount{ layerCount_ },
	layerSize{ layerSize_ },
	rng{ dev() }{
	if (layerCount < 2)
		throw exception("Need at least 2 layers");
}

NeuralNet::NeuralNet(NeuralNet&& other){
	input = other.input;
	output = other.output;
	layerCount = other.layerCount;
	layerSize = other.layerSize;

	other.input = nullptr;
	other.output = nullptr;
}

NeuralNet& NeuralNet::operator=(NeuralNet&& other){
	if (this != &other){
		input = other.input;
		output = other.output;
		layerCount = other.layerCount;
		layerSize = other.layerSize;

		other.input = nullptr;
		other.output = nullptr;
	}
	return *this;
}


NeuralNet::~NeuralNet(){
	if (input != nullptr)
		delete input;
}

void NeuralNet::CreateRandom(){
	vector<bitset<9>> layers;

	auto layer = CreateRandomLayer(layerSize);
	layers.insert(layers.begin(), layer.begin(), layer.end());

	for (int i = 1; i + 2 < layerCount; i++){
		auto layer = CreateRandomLayer(layerSize);
		layers.insert(layers.end(), layer.begin(), layer.end());
	}
	layer = CreateRandomLayer(layerSize);
	layers.insert(layers.end(), layer.begin(), layer.end());
	CreateByEncoding(layers);
}

void NeuralNet::CreateByEncoding(vector<bitset<9>>& encoding){

	auto iter = encoding.begin();
	Layer* curr = nullptr;

	for (int i = 0; i + 1 < layerCount; i++){

		vector<bitset<9>> layerEncoding(iter, iter + (layerSize*layerSize));

		auto next = new Layer(layerSize, layerEncoding);
		if (input == nullptr){
			input = next;
		}
		else{
			curr->SetNext(next);
			next->SetPrev(curr);
		}
		iter += (layerSize*layerSize);
		curr = next;
	}
	output = new Layer(layerSize);
	curr->SetNext(output);
	output->SetPrev(curr);
}

vector<double> NeuralNet::Simulate(std::vector<double>& inputValues){
	vector<double> out;

	if (inputValues.size() < layerSize)
		throw exception("Too less input values given!");

	input->ClearNodeSums();
	input->Simulate(inputValues);
	return output->GetNodeValues();
}

std::vector<double> NeuralNet::GetLastOutput() const{
	return output->GetNodeValues();
}

//TODO make not a vector of bitsets but one bitset, so that the bitset can be split at any pos -> problem bitset fixed length (->vector<bool>?)
vector<bitset<9>> NeuralNet::Encode() const{
	vector<bitset<9>> bits;

	for (auto layer = input; layer->GetNext() != nullptr; layer = layer->GetNext()){
		auto layerEncoding = layer->Encode();
		bits.insert(bits.end(), layerEncoding.begin(), layerEncoding.end());	//TODO maybe make with move
	}
	return bits;
}


vector<bitset<9>> NeuralNet::CreateRandomLayer(int layerSize){
	vector<bitset<9>> connections;

	for (int i = 0; i < layerSize * layerSize; i++){
		bitset<9> connection((rng() % 256) - 128);
		connection.set(8, true);
		connections.push_back(connection);
	}
	return connections;
}


