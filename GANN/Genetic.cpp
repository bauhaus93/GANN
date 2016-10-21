#include "Genetic.h"

using namespace std;

/*bool Fitness(pair<double, NeuralNet> const& a, pair<double, NeuralNet> const& b);
double GetScore(NeuralNet& net);

Genetic::Genetic(int populationSize, double mutationChance_) :
	rng{ dev() },
	mutationChance{ mutationChance_ } {

	for (int i = 0; i < populationSize; i++){
		NeuralNet n(4, 4);
		n.CreateRandom();
		population.push_back(make_pair(GetScore(n), move(n)));
	}

	sort(population.begin(), population.end(), Fitness);
}

Genetic::~Genetic(){
}

void Genetic::Run(int times){
	for (int i = 0; i < times; i++){
		RunOnce();
		if (i % 100 == 0)
			cout << "runs: " << i << endl;
	}
}

void Genetic::RunOnce(){
	auto selection = Select(4);

	auto parentA = population.at(selection.first).second.Encode();
	auto parentB = population.at(selection.second).second.Encode();

	auto child = Crossover(parentA, parentB);
	if (rng() % 100 / 100 < mutationChance)
		Mutate(child, 20);

	NeuralNet n(4, 4);
	n.CreateByEncoding(child);
	population.push_back(make_pair(GetScore(n), move(n)));
	sort(population.begin(), population.end(), Fitness);
	population.pop_back();
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

vector<bitset<9>> Genetic::Crossover(vector<bitset<9>> parentA, vector<bitset<9>> parentB){
	int splitPoint = rng() % parentA.size();
	vector<bitset<9>> child(parentA.begin(), parentA.begin() + splitPoint);
	child.insert(child.end(), parentB.begin() + splitPoint, parentB.end());
	return child;
}

void Genetic::Mutate(vector<bitset<9>>& individual, int flips){

	while (flips-- > 0){
		individual.at(rng() % individual.size()).flip(rng() % 9);
	}
}

std::vector<std::bitset<9>> Genetic::GetFittest(void){
	return population.front().second.Encode();
}

void Genetic::PrintPopulation(void){

	cout << "network outputs:" << endl;
	for (auto& p : population){
		cout << p.second.GetLastOutput().at(0) << "/";
	}
	cout << endl;
}

bool Fitness(pair<double, NeuralNet> const& a, pair<double, NeuralNet> const& b){
	return a.first > b.first;
}

double GetScore(NeuralNet& net){
	double score = 0;
	vector<double> input;
	vector<double> output;

	input.resize(4);
	for (int i = 0; i < 10; i++){
		for (int j = 0; j < 10; j++){
			input.at(0) = i;
			input.at(1) = j;
			output = net.Simulate(input);
			auto out = output.at(0);
			if (out < 0)
				continue;
			double prec = out / (i*j);
			if (prec > 1)
				score += 1 / prec;
			else if (prec <= 1){
				score += prec;
			}
		}
	}
	return score;
}*/