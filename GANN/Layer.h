#pragma once

#include <memory>
#include <vector>
#include <algorithm>

#include "Node.h"


class Layer{

private:

	std::vector<std::unique_ptr<Node>>	nodes;

	std::vector<std::unique_ptr<Node>>& GetNodes();

public:
							Layer(int nodeCount);
							~Layer();
	int						GetNodeCount() const;
	void					ClearNodeValues();
	int						Decode(std::vector<bool>& encoding, int start, Layer& next);
	int						Decode(std::vector<bool>& encoding, int start);

	Node&					operator[](int index);

	friend std::ostream&	operator<<(std::ostream& os, const Layer& layer);

};

