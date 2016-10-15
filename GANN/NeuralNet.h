#pragma once

#include <memory>
#include <vector>
#include <random>
#include <iostream>
#include <bitset>

#include "Layer.h"

class NeuralNet{

	Layer* input;
	Layer* output;
	int layerCount;
	int hiddenSize;
	int inputSize;
	int outputSize;

	std::random_device dev;
	std::mt19937 rng;

	std::vector<std::bitset<9>>	CreateRandomLayer(int srcSize, int destSize);

public:
								NeuralNet(int layerCount_, int hiddenSize_, int inputSize_, int outputSize_);
								~NeuralNet();
	void						CreateRandom();
	void						CreateByEncoding(std::vector<std::bitset<9>>& encoding);
	std::vector<double>			Simulate(std::vector<double>& inputValues);
	std::vector<std::bitset<9>>	Encode() const;

	

	
	
	
};

