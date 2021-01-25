#pragma once
#include <sstream>
#include <iomanip>

#define SIB_SCALE_MASK 0xC0
#define SIB_INDEX_MASK 0x38
#define SIB_BASE_MASK 0x7

typedef struct _SIB {
public:
	_SIB(char* p);

	std::string ToString();
	int Length();

	char GetScale();
	char GetIndex();
	char GetBase();

	int IsValid();
private:
	char* p;
	const char* REGISTER[8] = { "eax", "ecx", "edx", "ebx", "esp", "ebp", "esi", "edi" };
	const char* SCALEVALUE[4] = { "1", "2", "4", "8" };
}SIB, *LPSIB;