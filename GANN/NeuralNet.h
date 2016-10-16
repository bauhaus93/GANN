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
	int layerSize;

	std::random_device dev;
	std::mt19937 rng;

	std::vector<std::bitset<9>>	CreateRandomLayer(int layerSize);

public:

								NeuralNet(int layerCount_, int layerSize_);
								NeuralNet(NeuralNet&& other);
								NeuralNet(NeuralNet const& other) = delete;
	NeuralNet&					operator=(NeuralNet&& other);
								~NeuralNet();
	void						CreateRandom();
	void						CreateByEncoding(std::vector<std::bitset<9>>& encoding);
	std::vector<double>			Simulate(std::vector<double>& inputValues);
	std::vector<double>			GetLastOutput() const;
	std::vector<std::bitset<9>>	Encode() const;
	
};

	

