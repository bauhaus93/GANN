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



static double DistanceFromTarget(double is, double target, double min, double max);
static double GetScore(NeuralNet& net);
static int Distance(vector<bool> a, vector<bool> b);

Genetic::Genetic(int layerCount_, int layerSize_, int populationSize, double mutationChance_) :
	mutationChance{ mutationChance_ },
	layerCount{ layerCount_ },
	layerSize{ layerSize_ },
	repopulationData{ nullptr },
	diversityControlData{ nullptr }{
	random_device dev;
	rng.seed(dev());
	Populate(populationSize);
}

Genetic::~Genetic(){
}

uint64_t Genetic::Run(uint64_t times){
	uint64_t rate = 1e1;
	uint64_t i;

	for (i = 0; i < times; i++){
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

		if (repopulationData != nullptr){
			if (i % repopulationData->frequency == 0)
				Repopulate(population.size() * repopulationData->part);
		}

		if (diversityControlData != nullptr){
			if (i % diversityControlData->frequency == 0)
				ControlDiversity(diversityControlData->threshold);
		}

		if (population.front().score >= 4)
			break;
	}
	return i;
}

void Genetic::EnableRepopulation(int frequency, int partOfPopulation){
	repopulationData = make_unique<RepopulationData>(frequency, partOfPopulation);
}

void Genetic::EnableDiversityControl(int frequency, double minDiversity){
	diversityControlData = make_unique<DiversityControlData>(frequency, minDiversity);
}

void Genetic::Populate(int count){
	for (int i = 0; i < count; i++){
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

	double dist = PopulationDistance(child);

	NeuralNet n(layerCount, layerSize);
	n.Decode(child);
	population.emplace_back(GetScore(n), move(n), child);
	sort(population.begin(), population.end(), Fitness);
	population.pop_back();

}

void Genetic::ControlDiversity(double threshold){
	int killCount = 0;
	int minDistance = population.front().encoding.size() * threshold;

	for (auto iter = population.begin(); iter + 1 != population.end(); iter++){
		if (Distance(iter->encoding, (iter + 1)->encoding) < minDistance){
			(iter + 1)->score = 0;
			killCount++;
		}
	}

	sort(population.begin(), population.end(), Fitness);
	Repopulate(killCount);

}

pair<int, int> Genetic::Select(double step){
	double r1 = static_cast<double>(rng() % 100) / 100;
	double r2 = static_cast<double>(rng() % 100) / 100;
	size_t first = -1, second = -1;

	double chance = 1 / step;
	for (size_t i = 0; i < population.size(); i++){
		if (r1 < chance){
			first = i;
			break;
		}
		chance += chance / step;
	}

	if (first < 0)
		first = 0;


	chance = 1 / step;
	for (size_t i = 0; i < population.size(); i++){
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
		size_t pos = rng() % individual.size();
		individual.at(pos) = !individual.at(pos);
	}
}

vector<bool> Genetic::GetFittest(void){
	return population.front().encoding;
}

double Genetic::PopulationDistance(vector<bool> individual){
	int dist = Distance(population.front().encoding, individual);

	for (size_t i = 1; i < population.size(); i++){
		dist = min(dist, Distance(population.at(i).encoding, individual));
	}
	return static_cast<double>(dist) / (individual.size());
}

int Distance(vector<bool> a, vector<bool> b){
	int distance = 0;
	for (size_t i = 0; i < a.size(); i++){
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
	vector<double> values = XOR;

	input.resize(net.GetLayerSize());
	for (size_t i = 0; i < values.size(); i += 3){
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

RepopulationData::RepopulationData(int frequency_, double part_):
	frequency{ frequency_ },
	part{ part_ }{
}

DiversityControlData::DiversityControlData(int frequency_, double threshold_):
	frequency{ frequency_ },
	threshold{ threshold_ }{
}
