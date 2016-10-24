#pragma once

#include <memory>
#include <vector>
#include <random>
#include <iostream>
#include <bitset>

#include "Layer.h"
#include "utility.h"

class NeuralNet{

	std::vector<Layer*> layers;
	int					layerCount;
	int					layerSize;

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
	void						Simulate(std::vector<double>& input, std::vector<double>& output);
	std::vector<bool>			Encode() const;
	void						Decode(std::vector<bool>& encoding);
	int							DecodeLayer(std::vector<bool>& encoding, int start, Layer& srcLayer, Layer& destLayer);
	int							DecodeLayer(std::vector<bool>& encoding, int start, Layer& layer);
	int							DecodeNode(std::vector<bool>& encoding, int start, Node& node, Layer& destLayer);
	int							DecodeNode(std::vector<bool>& encoding, int start, Node & node);
	void						MinimizeNetwork();
	void						RemoveNonForwardingNodes();
	int							GetLayerCount() const;
	int							GetLayerSize() const;
	Layer&						operator[](int index);
	Node&						operator[](std::pair<int, int> index);

	friend std::ostream&		operator<<(std::ostream& os, const NeuralNet& net);
	
};



