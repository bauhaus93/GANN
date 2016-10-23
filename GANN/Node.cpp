#include "Node.h"

using namespace std;

Node::Node() : Node(0.0){
}


Node::Node(double bias_) :
	bias{ bias_ },
	value{ 0.0 }{
}

Node::~Node(){
}

void Node::SetBias(double bias_){
	bias = bias_;
}

void Node::Clear(void){
	value = 0;
}

double Node::GetOutput(void) const{
	return 1 / (1 + exp(-value));
}

Connection& Node::operator[](int index){
	return connections.at(index);
}

int Node::Decode(std::vector<bool>& encoding, int start, vector<unique_ptr<Node>>& destNodes){
	int pos = start;
	double bias = BoolVectorToDouble(encoding, pos);
	SetBias(bias);
	pos += 8 * sizeof(double);
	
	for (auto& node : destNodes){
		if (encoding.at(pos) == true){
			double weight = BoolVectorToDouble(encoding, pos);
			connections.emplace_back(*node, weight);
		}
		pos += 1 + 8 * sizeof(double);
	}
	return pos;
}

int Node::Decode(std::vector<bool>& encoding, int start, int layerSize){
	int pos = start;
	double bias = BoolVectorToDouble(encoding, pos);
	SetBias(bias);
	pos += 8 * sizeof(double);
	return pos + layerSize * (1 + 8 * sizeof(double));
}

Connection::Connection(Node& dest_, double weight_) :
	dest{ dest_ },
	weight{ weight_ }{
}

Connection::~Connection(){
}

Node& Connection::GetDest() const{
	return dest;
}

double Connection::GetWeight() const{
	return weight;
}

ostream& operator<<(ostream& os, const Connection& conn){
	os << "  connected with " << "something" << ", weight = " << conn.weight << endl;
	return os;
}

std::ostream& operator<<(std::ostream& os, const Node& node){
	os << "  node bias: " << node.bias << endl;
	for (const auto& conn : node.connections){
		os << "    " << conn;
	}
	return os;
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

double BoolVectorToDouble(vector<bool>& vec, int start){
	union{ uint64_t u; double d; } converter;
	int end = start + 8 * sizeof(double);
	converter.u = 0;

	for (int i = start; i < end; i++){
		converter.u |= vec.at(i);
		if (i + 1 < end)
			converter.u <<= 1;
	}
	return converter.d;
}
