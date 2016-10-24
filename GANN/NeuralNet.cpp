#include "NeuralNet.h"

using namespace std;

NeuralNet::NeuralNet(int layerCount_, int layerSize_) :
	layerCount{ layerCount_ },
	layerSize{ layerSize_ },
	rng{ dev() }{

	for (int i = 0; i < layerCount; i++){
		auto layer = new Layer(layerSize);
		layers.push_back(layer);
	}
}

NeuralNet& NeuralNet::operator=(NeuralNet&& other){
	if (this != &other){

	}
	return *this;
}

NeuralNet::~NeuralNet(){

}

void NeuralNet::CreateRandom(){
	vector<bool> encoding;

	for (int i = 0; i < layerCount; i++){
		auto layer = CreateRandomLayer();
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
		output.push_back((*out)[i].GetValue());
	}
}


vector<bool> NeuralNet::Encode() const{
	vector<bool> encoding;
	return encoding;
}

void NeuralNet::Decode(std::vector<bool>& encoding){
	int pos = 0;

	for (int i = 0; i + 1 < layerCount; i++){
		pos = DecodeLayer(encoding, pos, *layers.at(i), *layers.at(i + 1));
	}

	pos = DecodeLayer(encoding, pos, *layers.back());

	MinimizeNetwork();

	if (pos != encoding.size())
		throw;
}

int NeuralNet::DecodeLayer(vector<bool>& encoding, int start, Layer& srcLayer, Layer& destLayer){
	int pos = start;

	for (int i = 0; i < srcLayer.GetNodeCount(); i++){
		pos = DecodeNode(encoding, pos, srcLayer[i], destLayer);
	}
	return pos;
}

int NeuralNet::DecodeLayer(vector<bool>& encoding, int start, Layer& layer){
	int pos = start;

	for (int i = 0; i < layerSize; i++){
		pos = DecodeNode(encoding, pos, layer[i]);
	}
	return pos;
}

int NeuralNet::DecodeNode(vector<bool>& encoding, int start, Node& node, Layer& destLayer){
	int pos = start;
	double bias = BoolVectorToDouble(encoding, pos);
	pos += 8 * sizeof(double);

	node.SetBias(bias);
	for (int i = 0; i < layerSize; i++){
		bool active = encoding.at(pos);
		double weight = BoolVectorToDouble(encoding, pos + 1);
		node.AddConnection(active, destLayer[i], weight);
		pos += 1 + 8 * sizeof(double);
	}
	return pos;
}

int NeuralNet::DecodeNode(vector<bool>& encoding, int start, Node& node){
	int pos = start;
	double bias = BoolVectorToDouble(encoding, pos);
	pos += 8 * sizeof(double);

	node.SetBias(bias);

	return pos + (1 + 8 * sizeof(double)) * layerSize;
}

void NeuralNet::MinimizeNetwork(){

	//int maxDepth = layers.at(0)->GetMaxDepth();

	//cout << "max depth from input: " << maxDepth << endl;
}

void NeuralNet::RemoveNonForwardingNodes(){

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
			bool active = true;// && rng() % 100 < 75 ? false : true;
			double weight = rnDb(dev);
			auto weightVec = DoubleToBoolVector(weight);

			encoding.push_back(active);
			encoding.insert(encoding.end(), weightVec.begin(), weightVec.end());
		}
	}

	return encoding;
}

std::ostream& operator<<(std::ostream& os, const NeuralNet& net){
	os << "neural net: " << net.GetLayerCount() << " layers, " << net.GetLayerSize() << " max nodes per layer" << endl;
	for (auto& layer : net.layers)
		os << *layer;
	return os;
}