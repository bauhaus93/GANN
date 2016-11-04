#include "Genetic.h"

using namespace std;

#define AND {	0, 0, 0,\
				0, 1, 0,\
				1, 0, 0,\
				1, 1, 1}

#define OR {	0, 0, 0,\
				0, 1, 1,\
				1, 0, 1,\
				1, 1, 1}

#define NOR {	0, 0, 1,\
				0, 1, 0,\
				1, 0, 0,\
				1, 1, 0}

#define NAND {	0, 0, 1,\
				0, 1, 1,\
				1, 0, 1,\
				1, 1, 0}

#define IMPL {	0, 0, 1,\
				0, 1, 1,\
				1, 0, 0,\
				1, 1, 1}

#define XOR {	0, 0, 0,\
				0, 1, 1,\
				1, 0, 1,\
				1, 1, 0}

Genetic::Genetic(int layerCount_, int layerSize_, int populationSize, double mutationChance_) :
	layerCount{ layerCount_ },
	layerSize{ layerSize_ },
	rng{ dev() },
	mutationChance{ mutationChance_ }{

	Populate(populationSize);
}

Genetic::~Genetic(){
}

void Genetic::Run(int times){
	uint64_t rate = 1e1;

	for (uint64_t i = 0; i < times; i++){
		RunOnce();
		if (i % rate == 0){

			if (i == 1e2)
				rate = 1e2;
			else if (i == 1e3)
				rate = 1e4;
			else if (i == 1e6)
				rate = 1e5;


			if (i >= 1e6){
				cout << "runs: " << (i / 1e6) << "M, fittest: " << population.front().score << endl;
			}
			else if (i >= 1e3)
				cout << "runs: " << (i / 1e3) << "k, fittest: " << population.front().score << endl;
			else{
				cout << "runs: " << i << ", fittest: " << population.front().score << endl;
			}
		}

		if (i % 1000 == 0)
			Repopulate(population.size() / 4);

		if (population.front().score >= 4)
			break;
	}
}

void Genetic::Populate(int populationSize){
	for (int i = 0; i < populationSize; i++){
		NeuralNet n(layerCount, layerSize);
		n.CreateRandom();
		auto encoding = n.Encode();
		population.emplace_back(GetScore(n), move(n), encoding);
	}

	sort(population.begin(), population.end(), Fitness);
}

void Genetic::Repopulate(int n){
	population.erase(population.end() - n, population.end());
	Populate(n);
}

void Genetic::RunOnce(){
	auto selection = Select(4);

	auto parentA = population.at(selection.first).encoding;
	auto parentB = population.at(selection.second).encoding;

	auto child = Crossover(parentA, parentB);
	if ((rng() % 100) / 100 < mutationChance)
		Mutate(child, child.size() * 0.05);

	if (PopulationDistance(child) > 0.05){
		NeuralNet n(layerCount, layerSize);
		n.Decode(child);
		population.emplace_back(GetScore(n), move(n), child);
		sort(population.begin(), population.end(), Fitness);
		population.pop_back();
	}
}

pair<int, int> Genetic::Select(double step){
	double r1 = static_cast<double>(rng() % 100) / 100;
	double r2 = static_cast<double>(rng() % 100) / 100;
	int first = -1, second = -1;

	double chance = 1 / step;
	for (int i = 0; i < population.size(); i++){
		if (r1 < chance){
			first = i;
			break;
		}
		chance += chance / step;
	}

	if (first < 0)
		first = 0;


	chance = 1 / step;
	for (int i = 0; i < population.size(); i++){
		if (r2 < chance && i != first){
			second = i;
			break;
		}
		chance += chance / step;
	}

	if (second < 0){
		if (first == 0)
			second = 1;
		else
			second = 0;
	}
	return make_pair(first, second);
}

vector<bool> Genetic::Crossover(vector<bool> parentA, vector<bool> parentB){
	int splitPoint = rng() % parentA.size();
	vector<bool> child(parentA.begin(), parentA.begin() + splitPoint);
	child.insert(child.end(), parentB.begin() + splitPoint, parentB.end());
	return child;
}

void Genetic::Mutate(vector<bool>& individual, int flips){

	while (flips-- > 0){
		auto& bit = individual.at(rng() % individual.size());
		bit = !bit;
	}
}

vector<bool> Genetic::GetFittest(void){
	return population.front().encoding;
}

double Genetic::PopulationDistance(vector<bool> individual){
	int dist = Distance(population.front().encoding, individual);

	for (int i = 1; i < population.size(); i++){
		dist = min(dist, Distance(population.at(i).encoding, individual));
	}
	return static_cast<double>(dist) / (individual.size());
}

int Distance(vector<bool> a, vector<bool> b){
	int distance = 0;
	for (int i = 0; i < a.size(); i++){
		if (a.at(i) != b.at(i))
			distance++;
	}
	return distance;
}

bool Fitness(Individual const& a, Individual const& b){
	return a.score > b.score;
}

double GetScore(NeuralNet& net){
	double score = 0;
	vector<double> input;
	vector<double> output;
	vector<double> values = AND;

	input.resize(net.GetLayerSize());
	for (int i = 0; i < values.size(); i += 3){
		input.at(0) = values.at(i);
		input.at(1) = values.at(i+1);
		net.Simulate(input, output);
		double result = output.at(0);
		if (result < -1 || result > 1)
			return 0;
		score += 1 - DistanceFromTarget(result, values.at(i+2), -1, 1);
	}
	return score;
}

double DistanceFromTarget(double is, double target, double min, double max){
	if (is > target)
		swap(is, target);
	if (min > max)
		swap(min, max);
	return (target - is) / (max-min);
}

Individual::Individual(double score_, NeuralNet && nn, std::vector<bool>& encoding_) :
	score{ score_ },
	network{ move(nn) },
	encoding{ encoding_ }{
}

Individual::Individual(Individual&& other) :
	score{ other.score },
	network{ move(other.network) },
	encoding{ other.encoding }{
}

Individual & Individual::operator=(Individual && other){
	if (this != &other){
		score = other.score;
		network = move(other.network);
		encoding = other.encoding;
	}
	return *this;
}
