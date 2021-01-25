#include "opcode.h"

#include <iostream>

_OPCODE::_OPCODE(char* p, Definition* d) {
	this->p = p;
	this->length = 0;
	this->pf = false;
	this->seg = DS;
	this->lpOPCD = CheckNextByte(this->p, d);
}

_OPCODE::_OPCODE() {}

void* _OPCODE::operator new(size_t stAllocateBlock, char* p, Definition* d) {
	LPOPCODE opc = (LPOPCODE)malloc(stAllocateBlock);
	if (opc) {
		opc->length = 0;
		opc->pf = false;
		opc->seg = DS;
		opc->p = p;
		opc->lpOPCD = opc->CheckNextByte(opc->p, d);
	}
	return opc;
}

int _OPCODE::Length() {
	return length;
}

const char* _OPCODE::GetMnemonic() {
	if (lpOPCD == nullptr)
		return "(bad)";
	return lpOPCD->mnemonic;
}

int _OPCODE::GetOprSize() {
	switch (lpOPCD->format)
	{
	case BYTE:
		return 0;
	case WORD:
		return 1;
	case DWORD:
		return 2;
	case ANY:
		return 2;
	case FULL:
		return 2;
	default:
		return NULL;
	}
}

LPOPCD _OPCODE::GetOpCodeDefinition() {
	return lpOPCD;
}

int _OPCODE::HasModRMByte() {
	if (lpOPCD->attributes & MODREGRM)
		return 1;
	return 0;
}

bool _OPCODE::HasPrefix() {
	return pf;
}

int _OPCODE::IsValid() {
	if (lpOPCD == nullptr)
		return 0;
	return 1;
}

LPOPCD _OPCODE::CheckNextByte(char* p, Definition* d) {
	length++;
	LPOPCD tmp = d->GetFirstByte(p[0]);

	if (tmp == nullptr)
		return nullptr;

	if (tmp->attributes & TBOPCPREFIX) {
		pf = true;
		return CheckNextByte(&p[1], d);
	}

	if (tmp->attributes & SEGMENTPREFIX) {
		seg = tmp->ops[0];
		return CheckNextByte(&p[1], d);
	}

	if (HasPrefix()) {
		tmp = d->GetExtendedByte(p[0]);
	}
	else {
		tmp = d->GetFirstByte(p[0]);
	}

	if (tmp == nullptr)
		return nullptr;

	return tmp;
}