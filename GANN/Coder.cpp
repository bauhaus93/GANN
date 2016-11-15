#include "Coder.h"

using namespace std;

Coder::Coder(std::vector<bool>& code_, std::vector<Layer*>& layers_, int layerCount_, int layerSize_) :
	code{ code_ },
	layers{ layers_ },
	layerCount{ layerCount_ },
	layerSize{ layerSize_ },
	pos{ 0 }{

}

Coder::~Coder(){
}


CodeError::CodeError(string msg) noexcept:
runtime_error(msg.c_str()){
}

DecodeError::DecodeError(string msg) noexcept :
	CodeError("decode error: " + msg){
}

EncodeError::EncodeError(string msg) noexcept :
	CodeError("encode error: " + msg){
}

DecodeErrorInvalidIndex::DecodeErrorInvalidIndex(int readPos, int max) noexcept :
	DecodeError("tried to access invalid index: " + to_string(readPos) + "/" + to_string(max)){
}

DecodeErrorBitsReadMismatch::DecodeErrorBitsReadMismatch(int is, int should) noexcept :
	DecodeError("bits read does not equals bit amount: " + to_string(is) + "/" + to_string(should)){
}
