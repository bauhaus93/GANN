#pragma once

#include <memory>
#include <map>
#include <utility>
#include <vector>
#include <random>
#include <iostream>
#include <bitset>

#include "Layer.h"

static std::vector<bool> DoubleToBoolVector(double value);
static double BoolVectorToDouble(std::vector<bool>& vec, int from, int to);

class NeuralNet{

	std::vector<Layer> layers;
	const int layerCount;
	const int layerSize;

	std::random_device dev;
	std::mt19937 rng;

	std::vector<bool>			CreateRandomLayer(void);
	int							DecodeLayer(std::vector<bool>& encoding, int start);
	void						ValidateNetwork();

	bool						CheckNodeConnections(std::pair<int, int> from, std::pair<int, int> to);


public:

								NeuralNet(int layerCount_, int layerSize_);
								//NeuralNet(NeuralNet&& other);
								NeuralNet(NeuralNet const& other) = delete;
	NeuralNet&					operator=(NeuralNet&& other);
								~NeuralNet();
	void						CreateRandom();
	void						CreateByEncoding(std::vector<bool>& encoding);
	std::vector<double>			Simulate(std::vector<double>& inputValues);
	std::vector<bool>			Encode() const;
	int							GetLayerCount() const;
	int							GetLayerSize() const;
	Layer&						operator[](int index);
	Node&						operator[](std::pair<int, int> index);

	friend std::ostream&		operator<<(std::ostream& os, const NeuralNet& net);
	
};



