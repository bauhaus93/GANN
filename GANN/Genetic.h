#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <random>
#include <memory>

#include "NeuralNet.h"

typedef struct Individual{
	double				score;
	NeuralNet			network;
	std::vector<bool>	encoding;
	Individual(double score_, NeuralNet&& nn, std::vector<bool>& encoding);
	Individual(Individual&& other);
	Individual& operator=(Individual&& other);
};

bool Fitness(Individual const& a, Individual const& b);
static int Distance(std::vector<bool> a, std::vector<bool> b);
static double GetScore(NeuralNet& net);
static double DistanceFromTarget(double is, double target, double min, double max);



//TODO save population as encoded bitstring with its fitness value
class Genetic{

	std::vector<Individual> population;
	double mutationChance;
	int layerCount;
	int layerSize;

	std::random_device dev;
	std::mt19937 rng;

	std::pair<int, int> Select(double step);
	std::vector<bool> Crossover(std::vector<bool> parentA, std::vector<bool> parentB);
	void Mutate(std::vector<bool>& individual, int flips);

	void				Populate(int populationSize);
	void				Repopulate(int n);
	double				PopulationDistance(std::vector<bool> individual);
	void				RunOnce();

public:
						Genetic(int layerCount_, int layerSize_, int populationSize, double mutationChance);
						~Genetic();

	void				Run(int times);
	std::vector<bool>	GetFittest(void);

};



