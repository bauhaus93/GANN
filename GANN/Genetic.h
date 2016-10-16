#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <random>
#include <memory>

#include "NeuralNet.h"

//TODO save population as encoded bitstring with its fitness value
class Genetic{

	std::vector<std::pair<double, NeuralNet>> population;
	double mutationChance;

	std::random_device dev;
	std::mt19937 rng;

public:
	Genetic(int populationSize, double mutationChance);
	~Genetic();
	void Run(int times);

	void RunOnce();

	std::pair<int, int> Select(double step);
	std::vector<std::bitset<9>> Crossover(std::vector<std::bitset<9>> parentA, std::vector<std::bitset<9>> parentB);
	void Mutate(std::vector<std::bitset<9>>& individual, int flips);
	std::vector<std::bitset<9>> GetFittest(void);
	void PrintPopulation(void);
};

