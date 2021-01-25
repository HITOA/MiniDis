#include <iostream>

#include "instruction.h"

int main() {

	const char* p = "\x69\x04\x3D\x24\x58\x43\xFF\x3F\x23\x02\x27";

	Definition d;
	
	Instruction inst((char*)p, &d);

	printf("%s", inst.ToString().c_str());

	return 0;
}