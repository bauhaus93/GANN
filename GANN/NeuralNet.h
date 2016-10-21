#pragma once

#include <memory>
#include <vector>
#include <random>
#include <iostream>
#include <bitset>

#include "Layer.h"

std::vector<bool> DoubleToBoolVector(double value);
double BoolVectorToDouble(std::vector<bool>& vec, int from, int to);

class NeuralNet{

	std::vector<Layer> layers;
	int layerCount;
	int layerSize;

	std::random_device dev;
	std::mt19937 rng;

	std::vector<bool>			CreateRandomLayer(void);
	int							DecodeLayer(std::vector<bool>& encoding, int start);


public:

								NeuralNet(int layerCount_, int layerSize_);
								NeuralNet(NeuralNet&& other);
								NeuralNet(NeuralNet const& other) = delete;
	NeuralNet&					operator=(NeuralNet&& other);
								~NeuralNet();
	void						CreateRandom();
	void						CreateByEncoding(std::vector<bool>& encoding);
	std::vector<double>			Simulate(std::vector<double>& inputValues);
	std::vector<bool>			Encode() const;

	
	
};

	

