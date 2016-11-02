#include "Decoder.h"

using namespace std;

Decoder::Decoder(vector<bool>& code_, vector<Layer*>& layers_, int layerCount_, int layerSize_) :
	Coder(code_, layers_, layerCount_, layerSize_){
}


Decoder::~Decoder(){
}

void Decoder::Run(){

	for (int i = 0; i + 1 < layerCount; i++){
		try{
			DecodeLayer(*layers.at(i), *layers.at(i + 1));
		}
		catch (const out_of_range& e){
			throw DecodeErrorInvalidIndex(pos, code.size());
		}
	}

	DecodeLayer(*layers.back());
	if (pos != code.size())
		throw DecodeErrorBitsReadMismatch(pos, code.size());
}

void Decoder::DecodeLayer(Layer& srcLayer, Layer& destLayer){
	for (int i = 0; i < srcLayer.GetNodeCount(); i++){
		DecodeNode(srcLayer[i], destLayer);
	}
}

void Decoder::DecodeLayer(Layer& layer){
	for (int i = 0; i < layerSize; i++){
		DecodeNode(layer[i]);
	}
}

void Decoder::DecodeNode(Node& node, Layer& destLayer){
	double bias = BoolVectorToDouble(code, pos);
	pos += 8 * sizeof(double);

	node.SetBias(bias);
	for (int i = 0; i < layerSize; i++){
		bool active = code.at(pos);
		double weight = BoolVectorToDouble(code, pos + 1);
		node.AddConnection(active, destLayer[i], weight);
		pos += 1 + 8 * sizeof(double);
	}
}

void Decoder::DecodeNode(Node& node){
	double bias = BoolVectorToDouble(code, pos);
	pos += 8 * sizeof(double);

	node.SetBias(bias);

	pos += (1 + 8 * sizeof(double)) * layerSize;
}
