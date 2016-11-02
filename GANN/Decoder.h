#pragma once

#include <exception>

#include "Coder.h"
#include "Layer.h"
#include "utility.h"

class Decoder :
	public Coder{

	void DecodeLayer(Layer & srcLayer, Layer & destLayer);
	void DecodeLayer(Layer & layer);
	void DecodeNode(Node & node, Layer & destLayer);
	void DecodeNode(Node & node);
public:
	Decoder(std::vector<bool>& code_, std::vector<Layer*>& layers_, int layerCount_, int layerSize_);
	~Decoder();
	void Run();

};

