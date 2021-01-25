#pragma once
#include "opcode.h"
#include "modrm.h"

class Instruction {
public:
	Instruction(char* p, Definition* d);

	std::string ToString();
private:
	char* p;
	LPOPCODE opCode;
	int ParseIMM(char* p, int s, std::stringstream* out);
};