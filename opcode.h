#pragma once
#include "definition.h"

typedef struct _OPCODE {
public:
	_OPCODE();
	_OPCODE(char* p, Definition* d);

	void* operator new(size_t stAllocateBlock, char* p, Definition* d);

	int Length();
	const char* GetMnemonic();
	LPOPCD GetOpCodeDefinition();
	int GetOprSize();

	bool HasPrefix();
	int HasModRMByte();
	//int IsExtendedOpCode();
	int IsValid();
private:
	char* p;
	LPOPCD lpOPCD;
	int length;
	bool pf;
	int seg;
	LPOPCD CheckNextByte(char* p, Definition* d);
}OPCODE, *LPOPCODE;