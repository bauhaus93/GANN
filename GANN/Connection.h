#pragma once

#include <memory>
#include <iostream>

class Connection{

private:
	int dest;
	double weight;

public:
				Connection(int dest_, double weight_);
				~Connection();

	int			GetDest() const;
	double		GetWeight() const;
};

std::ostream& operator<<(std::ostream& os, const Connection& conn);

