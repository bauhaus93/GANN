#pragma once

#include <memory>
#include <vector>
#include <sstream>
#include <cmath>
#include <bitset>
#include <algorithm>

#include "Connection.h"


class Layer{

private:
	Layer* next;
	Layer* prev;

	std::vector<Connection> connections;
	std::vector<double>		nodeValues;

	double slope;
	int nodeCount;

	void							SetPreviousLayer(Layer* prev_);
	void							IncreaseNodeValue(int nodeIndex, double value);
	

public:
									Layer(int nodeCount_);
									Layer(int nodeCount_, int nextNodeCount, std::vector<std::bitset<9>> layerEncoding);
									~Layer();
	int								GetNodeCount() const;
	const std::vector<Connection>&	GetConnections() const;
	Layer*							GetNext() const;
	const std::vector<double>&		GetNodeValues() const;
	void							Simulate(std::vector<double>& input);
	void							ClearNodeSums();
	double							CalculateActivation(double input);
	std::vector<std::bitset<9>>		Encode() const;
	void							SetNext(Layer* next_);
	void							SetPrev(Layer* prev_);

};

std::ostream& operator<<(std::ostream& os, const Layer& layer);