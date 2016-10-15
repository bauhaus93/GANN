#pragma once

#include <memory>
#include <iostream>

class Connection{

private:
	bool active;
	int srcPos;
	int destPos;
	int8_t weight;

public:
				Connection(int srcPos, int destPos, bool active_, int8_t weight_);
				~Connection();

	int			GetSrc() const;
	int			GetDest() const;
	int8_t		GetWeight() const;
	bool		IsActive() const;
};

std::ostream& operator<<(std::ostream& os, const Connection& conn);

