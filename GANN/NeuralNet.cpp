#include "NeuralNet.h"

using namespace std;

NeuralNet::NeuralNet(int layerCount_, int layerSize_) :
	layerCount{ layerCount_ },
	layerSize{ layerSize_ },
	rng{ dev() }{
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

	CreateByEncoding(layers);
}

void NeuralNet::CreateByEncoding(vector<bool>& encoding){
	int pos = 0;

	for (int i = 0; i < layerCount; i++){
		pos = DecodeLayer(encoding, pos);
	}
	ValidateNetwork();
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

int NeuralNet::DecodeLayer(vector<bool>& encoding, int start){
	int pos = start;
	constexpr int connSize = 1 + 8 * sizeof(double);

	//TODO rearrange node connection destinations in prev layer if in curr layer a node gets deleted!
	layers.emplace_back();
	Layer& curr = layers.back();

	for (int i = 0; i < layerSize; i++){	//for each node

		if (layers.size() > 1 && !layers.at(layers.size() - 2).ConnectsWithNode(i)){
			pos += 8 * sizeof(double) + layerSize * connSize;
			continue;
		}

		double bias = BoolVectorToDouble(encoding, pos, pos + 8 * sizeof(double));
		curr.AddNode(bias);
		pos += 8 * sizeof(double);

		for (int j = 0; j < layerSize; j++){	//for each node in next layer (=connection)
			bool active = encoding.at(pos);

			if (active){
				double weight = BoolVectorToDouble(encoding, pos + 1, pos + connSize);
				try{
					curr[i].AddConnection(j, weight);
				}
				catch (out_of_range& e){
					//cout << e.what() << endl;
				}
			}
			pos += connSize;
		}
	}
	return pos;
}

void NeuralNet::ValidateNetwork(){
	map<pair<int, int>, bool> hasThroughput;

	for (int i = 0; i < layerCount; i++){
		for (int j = 0; j < layerSize; j++){
			auto index = make_pair(i, j);
			hasThroughput.emplace(index, false);
		}
	}
}

bool NeuralNet::CheckNodeConnections(pair<int, int> from, pair<int, int> to){
	auto pos = from;
	
	return true;

}

vector<bool> DoubleToBoolVector(double value){
	union{ uint64_t u; double d; } converter;
	vector<bool> result;

	converter.d = value;

	while (result.size() < 8 * sizeof(double)){
		result.insert(result.begin(), (converter.u & 1));
		converter.u >>= 1;
	}

	return result;
}

double BoolVectorToDouble(vector<bool>& vec, int from, int to){
	union{ uint64_t u; double d; } converter;
	converter.u = 0;

	for (int i = from; i < to; i++){
		converter.u |= vec.at(i);
		if (i + 1 < to)
			converter.u <<= 1;
	}
	return converter.d;
}

std::ostream& operator<<(std::ostream& os, const NeuralNet& net){
	os << "neural net: " << net.GetLayerCount() << " layers, " << net.GetLayerSize() << " max nodes per layer" << endl;
	for (auto& layer : net.layers)
		os << layer;
	return os;
}


