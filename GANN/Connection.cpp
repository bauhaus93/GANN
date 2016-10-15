#include "Connection.h"

using namespace std;

Connection::Connection(int srcPos_, int destPos_, bool active_, int8_t weight_) :
	active{ active_ },
	srcPos{ srcPos_ },
	destPos{ destPos_ },
	weight{ weight_ }{
}

Connection::~Connection(){
}

int Connection::GetSrc() const{
	return srcPos;
}

int Connection::GetDest() const{
	return destPos;
}

int8_t Connection::GetWeight() const{
	return weight;
}

bool Connection::IsActive() const{
	return active;
}

ostream& operator<<(ostream& os, const Connection& conn){
	os << "\tconnect " << conn.GetSrc() << " with " << conn.GetDest() << ", weight = " << static_cast<int>(conn.GetWeight()) << endl;
	return os;
}