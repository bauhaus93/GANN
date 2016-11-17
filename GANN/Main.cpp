#include <iostream>
#include <vector>


#include "NeuralNet.h"
#include "Genetic.h"
#include "Drawer.h"
#include "Tests.h"

using namespace std;

void PrintVector(vector<double>& vec, string title);
void DrawNetwork(Drawer& drawer, NeuralNet& net, int startX, int startY, int width, int height);
extern bool RunTests(void);


int main(int argc, char **argv){
	const int runs = 1e7;
	const int layerCount = 3;
	const int layerSize = 2;
	const int populationSize = 20;
	const double mutationChance = 0.05;

	Genetic g(layerCount, layerSize, populationSize, mutationChance);
	g.EnableDiversityControl(1e3, 0.33);
	g.EnableRepopulation(1e5, 0.25);
	auto times = g.Run(runs);
	
	cout << "found optimal after " << times << " runs" << endl;
	
	auto netCode = g.GetFittest();

	NeuralNet nn(layerCount, layerSize);
	nn.Decode(netCode);
	vector<double> input;
	vector<double> output;

	input.resize(layerSize);
	for (int i = 0; i < 2; i++){
		for (int j = 0; j < 2; j++){
			input.at(0) = i;
			input.at(1) = j;
			nn.Simulate(input, output);
			cout << i << " OP " << j << " = " << output.at(0) << endl;

		}
	}

	Drawer d(1024, 768);
	DrawNetwork(d, nn, 0, 0, 1024, 768);
	al_rest(5.0);

	return 0;
}

void DrawNetwork(Drawer& drawer, NeuralNet& net, int startX, int startY, int width, int height){

	float rectX = width / net.GetLayerCount();
	float rectY = height / net.GetLayerSize();
	float circleSize = min(rectX, rectY) * 0.3;


	drawer.SetColor(0, 0, 0);
	drawer.Clear();
	for (int i = 0; i < net.GetLayerCount(); i++){
		auto& layer = net[i];
		for (int j = 0; j < layer.GetNodeCount(); j++){
			auto& node = layer[j];
			int x = startX + i * rectX + rectX / 2;
			int y = startY + j * rectY + rectY / 2;

			
			for (int k = 0; k < node.GetConnectionCount(); k++){
				auto& conn = node[k];
				if (conn.IsActive()){
					if (conn.GetWeight() < 0)
						drawer.SetColor(0xFF, 0, 0);
					else
						drawer.SetColor(0, 0xFF, 0);
					drawer.Line(x, y, x + rectX, startY + k * rectY + rectY / 2);
				}
			}

			drawer.SetColor(0xFF, 0xFF, 0xFF);
			drawer.Circle(x, y, circleSize / 2, true);

		}
	}
	drawer.SetColor(0xFF, 0xFF, 0xFF);
	drawer.Rect(startX, startY, width, height);
	drawer.Flip();

}

void PrintVector(vector<double>& vec, string title){
	cout << title;
	for (size_t i = 0; i < vec.size(); i++){
		cout << vec[i];
		if (i + 1 == vec.size())
			cout << endl;
		else
			cout << "/";
	}
}
