#pragma once

#include <memory>
#include <vector>
#include <sstream>

#include <bitset>
#include <algorithm>

#include "Connection.h"
#include "Node.h"


class Layer{

private:

	std::vector<Node>		nodes;

public:
							Layer();
							~Layer();
	int						GetNodeCount() const;
	void					ClearNodeValues();
	bool					ConnectsWithNode(int index) const;
	void					AddNode(double bias);

	Node&					operator[](int index);

	friend std::ostream&	operator<<(std::ostream& os, const Layer& layer);

};

