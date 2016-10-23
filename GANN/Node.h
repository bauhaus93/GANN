#pragma once

#include <memory>
#include <vector>
#include <cmath>

#include "Connection.h"

class Node{

	double bias;
	double value;

	std::vector<Connection> connections;

public:
				Node(double bias_);
				~Node();

	void		SetBias(double bias_);
	void		AddConnection(int targetIndex, double weight);
	void		DeleteConnection(int index);
	int			GetConnectionCount() const;
	void		Clear(void);
	double		GetOutput(void);
	bool		ConnectsWithNode(int index) const;
	void		FlushConnections();
	Connection&	operator[](int index);

	friend std::ostream&	operator<<(std::ostream& os, const Node& node);
};

