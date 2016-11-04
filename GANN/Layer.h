#pragma once

#include <memory>
#include <vector>
#include <algorithm>

#include "Node.h"


class Layer{

private:

	std::vector<Node*>	nodes;

public:
							Layer(int nodeCount);
							~Layer();

	void					MakeInput(std::vector<double>& input);
	std::vector<double>		GetOutput() const;
	void					FeedForward();
	int						GetNodeCount() const;
	void					ClearNodeValues();
	bool					HasConnections() const;

	Node&					operator[](int index);

	friend std::ostream&	operator<<(std::ostream& os, const Layer& layer);

};

