#include "Node.h"

using namespace std;

Node::Node() : Node(0.0){
}


Node::Node(double bias_) :
	bias{ bias_ },
	value{ 0.0 }{
}

Node::~Node(){
	while (!connections.empty()){
		delete connections.back();
		connections.pop_back();
	}
}

void Node::SetBias(double bias_){
	bias = bias_;
}

void Node::SetValue(double value_){
	value = value_;
}

void Node::ModValue(double input){
	value += input;
}

double Node::GetValue() const{
	return value;
}

double Node::GetBias() const{
	return bias;
}

void Node::AddConnection(bool active, Node & node, double weight){
	auto conn = new Connection(active, node, weight);
	connections.push_back(conn);
}

int Node::GetConnectionCount() const{
	return connections.size();
}

void Node::Clear(void){
	value = bias;
}

double Node::Activation() const{
	return 1 / (1 + exp(-value));
}

Connection& Node::operator[](int index){
	return *connections.at(index);
}

int Node::GetMaxDepth() const{
	int currMax = 0;

	for (auto& conn : connections){
		if (conn->IsActive()){
			int depth = conn->GetDest().GetMaxDepth() + 1;
			currMax = max(currMax, depth);
		}
	}
	return currMax;
}

void Node::FeedForward(){
	double output = Activation();

	for (auto& conn : connections){
		if (conn->IsActive()){
			conn->GetDest().ModValue(output * conn->GetWeight());
		}
	}
}

Connection::Connection(bool active_, Node& dest_, double weight_) :
	active{ active_ },
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

bool Connection::IsActive() const{
	return active;
}

std::ostream& operator<<(std::ostream& os, const Node& node){
	os << "  node bias: " << node.bias << endl;
	for (const auto& conn : node.connections){
		if (conn->IsActive()){
			os << *conn;
		}
	}
	return os;
}

ostream& operator<<(ostream& os, const Connection& conn){
	os << "      conn weight = " << conn.weight << endl;
	return os;
}