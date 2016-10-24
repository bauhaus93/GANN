#pragma once

#include <ostream>
#include <memory>
#include <vector>
#include <cmath>
#include <algorithm>

#include "utility.h"


class Connection;

class Node{

	double	bias;
	double	value;

	std::vector<Connection*> connections;

public:
				Node();
				Node(double bias_);
				Node(Node& other) = delete;
				~Node();

	void		SetBias(double bias_);
	void		SetValue(double value_);
	void		ModValue(double input);
	double		GetValue() const;
	void		AddConnection(bool active, Node& node, double weight);
	int			GetConnectionCount() const;
	void		Clear(void);
	double		Activation() const;
	int			GetMaxDepth() const;
	void		FeedForward();

	Connection&	operator[](int index);
	

	friend std::ostream&	operator<<(std::ostream& os, const Node& node);
};

class Connection{

private:
	bool		active;
	Node&		dest;
	double		weight;

public:
							Connection(bool active_, Node& dest_, double weight_);
							~Connection();

	Node&					GetDest() const;
	double					GetWeight() const;
	bool					IsActive() const;
	friend std::ostream&	operator<<(std::ostream& os, const Connection& conn);
};
