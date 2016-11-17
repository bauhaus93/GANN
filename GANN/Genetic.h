#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <random>
#include <memory>

#include "NeuralNet.h"

struct Individual{
	double				score;
	NeuralNet			network;
	std::vector<bool>	encoding;
	Individual(double score_, NeuralNet&& nn, std::vector<bool>& encoding);
	Individual(Individual&& other);
	Individual& operator=(Individual&& other);
};

struct RepopulationData{
	int frequency;
	double part;
	RepopulationData(int frequency_, double part);
};

struct DiversityControlData{
	int frequency;
	double threshold;
	DiversityControlData(int frequency_, double threshold_);
};


bool Fitness(Individual const& a, Individual const& b);



//TODO save population as encoded bitstring with its fitness value
class Genetic{

	std::vector<Individual> population;
	double mutationChance;
	int layerCount;
	int layerSize;

	std::unique_ptr<RepopulationData> repopulationData;
	std::unique_ptr<DiversityControlData> diversityControlData;

	std::mt19937 rng;

	std::pair<int, int> Select(double step);
	std::vector<bool> Crossover(std::vector<bool> parentA, std::vector<bool> parentB);
	void Mutate(std::vector<bool>& individual, int flips);

	void				Populate(int populationSize);
	void				Repopulate(int n);
	double				PopulationDistance(std::vector<bool> individual);
	void				RunOnce();

	void				ControlDiversity(double threshold);

public:
						Genetic(int layerCount_, int layerSize_, int populationSize, double mutationChance);
						~Genetic();

	uint64_t			Run(uint64_t times);
	void				EnableRepopulation(int runs, int partOfPopulation);
	void				EnableDiversityControl(int frequency, double minDiversity);
	std::vector<bool>	GetFittest(void);

};


