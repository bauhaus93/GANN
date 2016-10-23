#include "NeuralNet.h"

using namespace std;

NeuralNet::NeuralNet(int layerCount_, int layerSize_) :
	layerCount{ layerCount_ },
	layerSize{ layerSize_ },
	rng{ dev() }{

	for (int i = 0; i < layerCount; i++){
		layers.emplace_back(layerSize);
	}


}

/*NeuralNet::NeuralNet(NeuralNet&& other){

}*/

NeuralNet& NeuralNet::operator=(NeuralNet&& other){
	if (this != &other){

	}
	return *this;
}

NeuralNet::~NeuralNet(){

}

void NeuralNet::CreateRandom(){
	vector<bool> layers;

	for (int i = 0; i < layerCount; i++){
		auto layer = CreateRandomLayer();
		layers.insert(layers.end(), layer.begin(), layer.end());
	}

	Decode(layers);
}


vector<double> NeuralNet::Simulate(std::vector<double>& inputValues){

	if (inputValues.size() < layerSize)
		throw exception("Too less input values given!");

}


//TODO make not a vector of bitsets but one bitset, so that the bitset can be split at any pos -> problem bitset fixed length (->vector<bool>?)
vector<bool> NeuralNet::Encode() const{
	vector<bool> encoding;
	return encoding;
}

void NeuralNet::Decode(std::vector<bool>& encoding){
	int pos = 0;

	for (int i = 0; i + 1 < layerCount; i++){
		pos = layers.at(i).Decode(encoding, pos, layers.at(i + 1));
	}

	pos = layers.back().Decode(encoding, pos);

	if (pos != encoding.size())
		throw;
}

int NeuralNet::GetLayerCount() const{
	return layerCount;
}

int NeuralNet::GetLayerSize() const{
	return layerSize;
}

Layer& NeuralNet::operator[](int index){
	return layers.at(index);
}

Node & NeuralNet::operator[](std::pair<int, int> index){
	return layers.at(index.first)[index.second];
}

vector<bool> NeuralNet::CreateRandomLayer(void){
	vector<bool> encoding;
	uniform_real_distribution<double> rnDb(-10, 10);

	for (int i = 0; i < layerSize; i++){
		double bias = rnDb(dev);
		auto biasVec = DoubleToBoolVector(bias);
		encoding.insert(encoding.end(), biasVec.begin(), biasVec.end());

		for (int j = 0; j < layerSize; j++){
			bool active = true && rng() % 100 < 50 ? false : true;
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
		os << layer;
	return os;
}


