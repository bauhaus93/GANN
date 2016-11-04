#include "NeuralNet.h"

using namespace std;

NeuralNet::NeuralNet(int layerCount_, int layerSize_) :
	layerCount{ layerCount_ },
	layerSize{ layerSize_ },
	rng{ dev() }{

	if (layerCount < 2)
		throw NeuralNetError("layer count must be at least 2");
	if (layerSize < 0)
		throw NeuralNetError("layer size must be at least 1");

	for (int i = 0; i < layerCount; i++){
		auto layer = new Layer(layerSize);
		layers.push_back(layer);
	}
}

NeuralNet::NeuralNet(NeuralNet&& other){
	layerCount = other.layerCount;
	layerSize = other.layerSize;
	layers = other.layers;

	other.layers.clear();
}

NeuralNet& NeuralNet::operator=(NeuralNet&& other){
	if (this != &other){
		layerCount = other.layerCount;
		layerSize = other.layerSize;
		layers = other.layers;

		other.layers.clear();
	}
	return *this;
}

NeuralNet::~NeuralNet(){
	while (!layers.empty()){
		delete layers.back();
		layers.pop_back();
	}
}

void NeuralNet::CreateRandom(){
	vector<bool> encoding;

	for (int i = 0; i < layerCount; i++){
		auto layer = i + 1 < layerCount ? CreateRandomLayer() : CreateRandomOutputLayer();
		encoding.insert(encoding.end(), layer.begin(), layer.end());
	}

	Decode(encoding);
}

void NeuralNet::Simulate(std::vector<double>& input, vector<double>& output){

	for (auto& layer : layers)
		layer->ClearNodeValues();

	layers.at(0)->MakeInput(input);
	for (auto& layer : layers){
		layer->FeedForward();
	}

	auto& out = layers.back();
	output.clear();
	for (int i = 0; i < out->GetNodeCount(); i++){
		output.push_back((*out)[i].GetOutput());
	}
}

vector<bool> NeuralNet::Encode(){
	vector<bool> encoding;
	Encoder enc(encoding, layers, layerCount, layerSize);

	try{
		enc.Run();
	}
	catch (const CodeError& e){
		cout << e.what() << endl;
	}
	return encoding;
}

void NeuralNet::Decode(vector<bool>& encoding){
	Decoder dec(encoding, layers, layerCount, layerSize);

	try{
		dec.Run();
	}
	catch (const CodeError& e){
		cout << e.what() << endl;
	}
}

int NeuralNet::GetLayerCount() const{
	return layerCount;
}

int NeuralNet::GetLayerSize() const{
	return layerSize;
}

Layer& NeuralNet::operator[](int index){
	return *layers.at(index);
}

Node & NeuralNet::operator[](std::pair<int, int> index){
	return (*layers.at(index.first))[index.second];
}

vector<bool> NeuralNet::CreateRandomLayer(void){
	vector<bool> encoding;
	uniform_real_distribution<double> rnDb(-10, 10);

	for (int i = 0; i < layerSize; i++){
		double bias = rnDb(dev);
		auto biasVec = DoubleToBoolVector(bias);
		encoding.insert(encoding.end(), biasVec.begin(), biasVec.end());

		for (int j = 0; j < layerSize; j++){
			bool active = true;// && rng() % 100 < 25 ? false : true;
			double weight = rnDb(dev);
			auto weightVec = DoubleToBoolVector(weight);

			encoding.push_back(active);
			encoding.insert(encoding.end(), weightVec.begin(), weightVec.end());
		}
	}

	return encoding;
}

vector<bool> NeuralNet::CreateRandomOutputLayer(void){
	vector<bool> encoding;
	uniform_real_distribution<double> rnDb(-10, 10);

	for (int i = 0; i < layerSize; i++){
		double bias = 0;// rnDb(dev);
		auto biasVec = DoubleToBoolVector(bias);
		encoding.insert(encoding.end(), biasVec.begin(), biasVec.end());
	}
	return encoding;
}

std::ostream& operator<<(std::ostream& os, const NeuralNet& net){
	os << "neural net: " << net.GetLayerCount() << " layers, " << net.GetLayerSize() << " max nodes per layer" << endl;
	for (auto& layer : net.layers)
		os << *layer;
	return os;
}

NeuralNetError::NeuralNetError(std::string msg):
runtime_error("neural network error: " + msg){
}
