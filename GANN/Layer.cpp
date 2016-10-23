#include "Layer.h"

using namespace std;

std::vector<std::unique_ptr<Node>>& Layer::GetNodes(){
	return nodes;
}

Layer::Layer(int nodeCount){

	for (int i = 0; i < nodeCount; i++){
		nodes.emplace_back();
	}
}

Layer::~Layer(){

}
int Layer::GetNodeCount() const{
	return nodes.size();
}

void Layer::ClearNodeValues(){
	for (auto& node : nodes){
		node->Clear();
	}
}


int Layer::Decode(std::vector<bool>& encoding, int start, Layer& next){
	int pos = start;

	for (auto& node : nodes){
		pos = node->Decode(encoding, pos, next.GetNodes());
	}
	return pos;
}

int Layer::Decode(std::vector<bool>& encoding, int start){
	int pos = start;

	for (auto& node : nodes){
		pos = node->Decode(encoding, pos, nodes.size());
	}
	return pos;
}

Node& Layer::operator[](int index){
	return *nodes.at(index);
}

std::ostream& operator<<(std::ostream& os, const Layer& layer){
	os << "  layer node count: " << layer.nodes.size() << endl;
	for (const auto& node : layer.nodes){
		os << "  " << "i'm a node";
	}
	return os;
}
