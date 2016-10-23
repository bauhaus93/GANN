#include "Layer.h"

using namespace std;

Layer::Layer():
	nodes{}{

}

Layer::~Layer(){

}
int Layer::GetNodeCount() const{
	return nodes.size();
}

void Layer::ClearNodeValues(){
	for (auto& node : nodes){
		node.Clear();
	}
}

bool Layer::ConnectsWithNode(int index) const{
	for (auto& node : nodes){
		if (node.ConnectsWithNode(index))
			return true;
	}
	return false;
}

void Layer::AddNode(double bias){
	nodes.emplace_back(bias);
}

void Layer::FlushConnections(){
	for (auto& node : nodes)
		node.FlushConnections();
}

Node& Layer::operator[](int index){
	return nodes.at(index);
}

std::ostream& operator<<(std::ostream& os, const Layer& layer){
	os << "  layer node count: " << layer.nodes.size() << endl;
	for (const auto& node : layer.nodes){
		os << "  " << node;
	}
	return os;
}
