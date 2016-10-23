#include "Node.h"

using namespace std;


Node::Node(double bias_) :
	bias{ bias_ },
	value{ 0 }{
}

Node::~Node(){
}

void Node::SetBias(double bias_){
	bias = bias_;
}

void Node::AddConnection(int targetIndex, double weight){
	connections.emplace_back(targetIndex, weight);
}

void Node::Clear(void){
	value = 0;
}

double Node::GetOutput(void){
	return 1 / (1 + exp(-value));
}

bool Node::ConnectsWithNode(int index) const{
	for (auto& connection : connections){
		if (connection.GetDest() == index)
			return true;
	}
	return false;
}

std::ostream& operator<<(std::ostream& os, const Node& node){
	os << "  node bias: " << node.bias << endl;
	for (const auto& conn : node.connections){
		os << "    " << conn;
	}
	return os;
}
