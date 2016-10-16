#include "Layer.h"

using namespace std;



Layer::Layer(int nodeCount_) :
	next{ nullptr },
	prev{ nullptr },
	nodeCount{ nodeCount_ },
	slope{ 1.0 }{
	nodeValues.resize(nodeCount);

}

Layer::Layer(int nodeCount_, int nextNodeCount, std::vector<std::bitset<9>> layerEncoding) :
	Layer{ nodeCount_ }{

	int srcPos = 0;
	int destPos = 0;
	for(auto block : layerEncoding){
		bool active = block.test(8);
		block.set(8, 0);
		int8_t weight = static_cast<int8_t>(block.to_ulong());
		connections.emplace_back(srcPos, destPos, active, weight);
		destPos++;
		if (destPos >= nextNodeCount){
			destPos = 0;
			srcPos++;
		}
	}
}

Layer::~Layer(){
	if (next != nullptr)
		delete next;
}
int Layer::GetNodeCount() const{
	return nodeCount;
}

const std::vector<Connection>& Layer::GetConnections() const{
	return connections;
}

Layer* Layer::GetNext() const{
	return next;
}

const std::vector<double>& Layer::GetNodeValues() const{
	return nodeValues;
}

void Layer::Simulate(vector<double>& input){

	for (auto conn : connections){
		if (conn.IsActive())
			next->IncreaseNodeValue(conn.GetDest(), input.at(conn.GetSrc()) * static_cast<double>(conn.GetWeight()));
	}

	for (auto layer = next; layer->next != nullptr; layer = layer->GetNext()){
		vector<double> outputs;
		for (double nodeValue : layer->GetNodeValues()){
			double activation = CalculateActivation(nodeValue);
			outputs.push_back(activation);
		}
		for (auto conn : layer->connections){
			if (conn.IsActive())
				layer->next->IncreaseNodeValue(conn.GetDest(), outputs.at(conn.GetSrc()) * static_cast<double>(conn.GetWeight()));
		}
	}
}

void Layer::ClearNodeSums(){
	fill(nodeValues.begin(), nodeValues.end(), 0);
	if (next)
		next->ClearNodeSums();
}

double Layer::CalculateActivation(double input){
	return 1 / (1 + exp(-slope * input));
}

vector<bitset<9>> Layer::Encode() const{
	vector<bitset<9>> bits;

	for (auto conn : connections){
		bitset<9> bit(conn.GetWeight());
		bit.set(8, conn.IsActive());
		bits.push_back(bit);
	}
	return bits;
}

void Layer::SetNext(Layer * next_){
	next = next_;
}

void Layer::SetPrev(Layer * prev_){
	prev = prev_;
}

void Layer::IncreaseNodeValue(int nodeIndex, double value){
	nodeValues.at(nodeIndex) += value;
}

void Layer::SetPreviousLayer(Layer* prev_){
	prev = prev_;
}

ostream& operator<<(ostream& os, const Layer& layer){
	os << "layer node count: " << layer.GetNodeCount() << endl;

	os << "node values: ";
	for (const auto nodeValue : layer.GetNodeValues()){
		os << nodeValue << " ";
	}
	os << endl;

	for (const auto conn : layer.GetConnections()){
		os << conn;
	}
	if (layer.GetNext() != nullptr){
		os << *layer.GetNext();
	}
	return os;
}

