#pragma once

#include <vector>

#include "Coder.h"
#include "Layer.h"
#include "Utility.h"


class Encoder :
	public Coder{

	void EncodeLayer(Layer& layer);
	void EncodeOutputLayer(Layer & layer);
	void EncodeNode(Node& node);
	void EncodeOutputNode(Node & node);
public:
	Encoder(std::vector<bool>& code_, std::vector<Layer*>& layers_, int layerCount_, int layerSize_);
	~Encoder();
	void Run();

};

