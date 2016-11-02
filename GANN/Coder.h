#pragma once

#include <vector>
#include <sstream>

#include "Layer.h"

class Coder{

protected:
	std::vector<bool>&		code;
	std::vector<Layer*>&	layers;
	const int				layerCount;
	const  int				layerSize;
	unsigned int			pos;
public:
	Coder(std::vector<bool>& code_, std::vector<Layer*>& layers_, int layerCount_, int layerSize_);
	virtual ~Coder();
	virtual void Run() = 0;
};

class CodeError : public std::runtime_error{

public:
	explicit CodeError(std::string msg) noexcept;
};

class DecodeError : public CodeError{

public:
	explicit DecodeError(std::string msg) noexcept;
};

class DecodeErrorInvalidIndex : public DecodeError{

public:
	explicit DecodeErrorInvalidIndex(int readPos, int max) noexcept;
};

class DecodeErrorBitsReadMismatch : public DecodeError{

public:
	explicit DecodeErrorBitsReadMismatch(int is, int should) noexcept;
};


class EncodeError : public CodeError{

public:
	explicit EncodeError(std::string msg) noexcept;
};