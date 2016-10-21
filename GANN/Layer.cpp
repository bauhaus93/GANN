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

Node& Layer::operator[](int index){
	return nodes.at(index);
}


ostream& operator<<(ostream& os, const Layer& layer){
	os << "layer node count: " << layer.GetNodeCount() << endl;

	os << "node values: ";
	/*for (const auto nodeValue : layer.GetNodeValues()){
		os << nodeValue << " ";
	}
	os << endl;

	for (const auto conn : layer.GetConnections()){
		os << conn;
	}
	if (layer.GetNext() != nullptr){
		os << *layer.GetNext();
	}*/
	return os;
}

