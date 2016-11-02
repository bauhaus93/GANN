#include "Encoder.h"

using namespace std;

Encoder::Encoder(vector<bool>& code_, vector<Layer*>& layers_, int layerCount_, int layerSize_) :
	Coder(code_, layers_, layerCount_, layerSize_){
}

Encoder::~Encoder(){

}

void Encoder::Run(){
	for (int i = 0; i < layerCount - 1; i++)
		EncodeLayer(*layers.at(i));

	EncodeOutputLayer(*layers.back());
}

void Encoder::EncodeLayer(Layer& layer){
	for (int i = 0; i < layerSize; i++)
		EncodeNode(layer[i]);
}

void Encoder::EncodeOutputLayer(Layer& layer){
	for (int i = 0; i < layerSize; i++)
		EncodeOutputNode(layer[i]);
}

void Encoder::EncodeNode(Node& node){
	vector<bool> bias = DoubleToBoolVector(node.GetBias());

	code.insert(code.end(), bias.begin(), bias.end());

	for (int i = 0; i < layerSize; i++){
		bool active = node[i].IsActive();
		vector<bool> weight = DoubleToBoolVector(node[i].GetWeight());
		code.push_back(active);
		code.insert(code.end(), weight.begin(), weight.end());
	}
}

void Encoder::EncodeOutputNode(Node& node){
	vector<bool> bias = DoubleToBoolVector(node.GetBias());

	code.insert(code.end(), bias.begin(), bias.end());
}