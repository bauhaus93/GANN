#include "Layer.h"

using namespace std;

Layer::Layer(int nodeCount){

	for (int i = 0; i < nodeCount; i++){
		Node *n = new Node(i);
		nodes.push_back(n);
	}
}

Layer::~Layer(){
	while (!nodes.empty()){
		delete nodes.back();
		nodes.pop_back();
	}
}

void Layer::MakeInput(std::vector<double>& input){
	if (nodes.size() != input.size())
		throw runtime_error("input does not match input layer size");
	for (size_t i = 0; i < nodes.size(); i++){
		nodes.at(i)->SetValue(input.at(i));
	}
}

vector<double> Layer::GetOutput() const{
	vector<double> output;
	output.resize(nodes.size());
	for (size_t i = 0; i < nodes.size(); i++)
		output.at(i) = nodes[i]->GetOutput();
	return output;
}

void Layer::FeedForward(){
	for (auto& node : nodes){
		node->FeedForward();
	}
}

int Layer::GetNodeCount() const{
	return nodes.size();
}

void Layer::ClearNodeValues(){
	for (auto& node : nodes){
		node->Clear();
	}
}

bool Layer::HasConnections() const{
	for (auto& node : nodes){
		if (node->GetConnectionCount() > 0)
			return true;
	}
	return false;
}

Node& Layer::operator[](int index){
	return *nodes.at(index);
}

std::ostream& operator<<(std::ostream& os, const Layer& layer){
	os << "  layer node count: " << layer.nodes.size() << endl;
	for(size_t i = 0; i < layer.nodes.size(); i++)
		os << "  " << *layer.nodes.at(i);
	return os;
}
