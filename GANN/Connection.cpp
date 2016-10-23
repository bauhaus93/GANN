#include "Connection.h"

using namespace std;

Connection::Connection(int dest_, double weight_) :
	dest{ dest_ },
	weight{ weight_ }{
}

Connection::~Connection(){
}

int Connection::GetDest() const{
	return dest;
}

double Connection::GetWeight() const{
	return weight;
}

ostream& operator<<(ostream& os, const Connection& conn){
	os << "  connected with " << conn.dest << ", weight = " << conn.weight << endl;
	return os;
}