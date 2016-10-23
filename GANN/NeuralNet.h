#pragma once

#include <memory>
#include <vector>
#include <random>
#include <iostream>
#include <bitset>

#include "Layer.h"



class NeuralNet{

	std::vector<Layer> layers;
	const int layerCount;
	const int layerSize;

	std::random_device dev;
	std::mt19937 rng;

	std::vector<bool>			CreateRandomLayer(void);

public:

								NeuralNet(int layerCount_, int layerSize_);
								//NeuralNet(NeuralNet&& other);
								NeuralNet(NeuralNet const& other) = delete;
	NeuralNet&					operator=(NeuralNet&& other);
								~NeuralNet();
	void						CreateRandom();
	std::vector<double>			Simulate(std::vector<double>& inputValues);
	std::vector<bool>			Encode() const;
	void						Decode(std::vector<bool>& encoding);
	int							GetLayerCount() const;
	int							GetLayerSize() const;
	Layer&						operator[](int index);
	Node&						operator[](std::pair<int, int> index);

	friend std::ostream&		operator<<(std::ostream& os, const NeuralNet& net);
	
};



