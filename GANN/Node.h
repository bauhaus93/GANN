#pragma once

#include <ostream>
#include <memory>
#include <vector>
#include <cmath>
#include <algorithm>

static std::vector<bool> DoubleToBoolVector(double value);
static double BoolVectorToDouble(std::vector<bool>& vec, int start);

class Connection;

class Node{

	double bias;
	double value;

	std::vector<Connection> connections;

public:
				Node();
				Node(double bias_);
				Node(Node& other) = delete;
				~Node();

	void		SetBias(double bias_);
	void		Clear(void);
	double		GetOutput(void) const;
	Connection&	operator[](int index);
	int			Decode(std::vector<bool>& encoding, int start, std::vector<std::unique_ptr<Node>>& destNodes);
	int			Decode(std::vector<bool>& encoding, int start, int layerSize);

	friend std::ostream&	operator<<(std::ostream& os, const Node& node);
};

class Connection{

private:
	Node&		dest;
	double		weight;

public:
	Connection(Node& dest_, double weight_);
	~Connection();

	Node&					GetDest() const;
	double					GetWeight() const;
	friend std::ostream&	operator<<(std::ostream& os, const Connection& conn);
};
