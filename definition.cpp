#include "definition.h"
#include <iostream>

LPOPCD Definition::GetFirstByte(char b) {
	for (size_t i = 0; i < opcds.size(); i++) {
		if (opcds[i]->value[0] == b)
			return opcds[i];
	}
	return nullptr;
}

LPOPCD Definition::GetExtendedByte(char b) {
	for (size_t i = 0; i < extopcds.size(); i++) {
		if (extopcds[i]->value[0] == b)
			return extopcds[i];
	}
	return nullptr;
}

Definition::Definition() {
	InitOPCD();
	InitExtendedOPCD();
}

void Definition::InitOPCD() {
	opcds.push_back(new("\x00", "add", RM, R, BYTE, MODREGRM) OPCD);
	opcds.push_back(new("\x01", "add", RM, R, FULL, MODREGRM) OPCD);
	opcds.push_back(new("\x02", "add", R, RM, BYTE, MODREGRM) OPCD);
	opcds.push_back(new("\x03", "add", R, RM, FULL, MODREGRM) OPCD);
	opcds.push_back(new("\x04", "add", A, IMM, BYTE, NONE) OPCD);
	opcds.push_back(new("\x05", "add", A, IMM, FULL, NONE) OPCD);
	opcds.push_back(new("\x06", "push", ES, ANY, NONE) OPCD);
	opcds.push_back(new("\x07", "pop", ES, ANY, NONE) OPCD);

	opcds.push_back(new("\x08", "or", RM, R, BYTE, MODREGRM) OPCD);
	opcds.push_back(new("\x09", "or", RM, R, FULL, MODREGRM) OPCD);
	opcds.push_back(new("\x0A", "or", R, RM, BYTE, MODREGRM) OPCD);
	opcds.push_back(new("\x0B", "or", R, RM, FULL, MODREGRM) OPCD);
	opcds.push_back(new("\x0C", "or", A, IMM, BYTE, NONE) OPCD);
	opcds.push_back(new("\x0D", "or", A, IMM, FULL, NONE) OPCD);
	opcds.push_back(new("\x0E", "push", CS, ANY, NONE) OPCD);
	opcds.push_back(new("\x0F", TBOPCPREFIX) OPCD); //Two Byte Opcode

	opcds.push_back(new("\x10", "adc", RM, R, BYTE, MODREGRM) OPCD);
	opcds.push_back(new("\x11", "adc", RM, R, FULL, MODREGRM) OPCD);
	opcds.push_back(new("\x12", "adc", R, RM, BYTE, MODREGRM) OPCD);
	opcds.push_back(new("\x13", "adc", R, RM, FULL, MODREGRM) OPCD);
	opcds.push_back(new("\x14", "adc", A, IMM, BYTE, NONE) OPCD);
	opcds.push_back(new("\x15", "adc", A, IMM, FULL, NONE) OPCD);
	opcds.push_back(new("\x16", "push", SS, ANY, NONE) OPCD);
	opcds.push_back(new("\x17", "pop", SS, ANY, NONE) OPCD);

	opcds.push_back(new("\x18", "sbb", RM, R, BYTE, MODREGRM) OPCD);
	opcds.push_back(new("\x19", "sbb", RM, R, FULL, MODREGRM) OPCD);
	opcds.push_back(new("\x1A", "sbb", R, RM, BYTE, MODREGRM) OPCD);
	opcds.push_back(new("\x1B", "sbb", R, RM, FULL, MODREGRM) OPCD);
	opcds.push_back(new("\x1C", "sbb", A, IMM, BYTE, NONE) OPCD);
	opcds.push_back(new("\x1D", "sbb", A, IMM, FULL, NONE) OPCD);
	opcds.push_back(new("\x1E", "push", DS, ANY, NONE) OPCD);
	opcds.push_back(new("\x1F", "pop", DS, ANY, NONE) OPCD);

	opcds.push_back(new("\x20", "and", RM, R, BYTE, MODREGRM) OPCD);
	opcds.push_back(new("\x21", "and", RM, R, FULL, MODREGRM) OPCD);
	opcds.push_back(new("\x22", "and", R, RM, BYTE, MODREGRM) OPCD);
	opcds.push_back(new("\x23", "and", R, RM, FULL, MODREGRM) OPCD);
	opcds.push_back(new("\x24", "and", A, IMM, BYTE, NONE) OPCD);
	opcds.push_back(new("\x25", "and", A, IMM, FULL, NONE) OPCD);
	opcds.push_back(new("\x26", ES, SEGMENTPREFIX) OPCD); //ES SEGMENT OVERRIDE PREFIX
	opcds.push_back(new("\x27", "daa", A, BYTE, NONE) OPCD);

	opcds.push_back(new("\x28", "sub", RM, R, BYTE, MODREGRM) OPCD);
	opcds.push_back(new("\x29", "sub", RM, R, FULL, MODREGRM) OPCD);
	opcds.push_back(new("\x2A", "sub", R, RM, BYTE, MODREGRM) OPCD);
	opcds.push_back(new("\x2B", "sub", R, RM, FULL, MODREGRM) OPCD);
	opcds.push_back(new("\x2C", "sub", A, IMM, BYTE, NONE) OPCD);
	opcds.push_back(new("\x2D", "sub", A, IMM, FULL, NONE) OPCD);
	opcds.push_back(new("\x2E", CS, SEGMENTPREFIX) OPCD); //CS SEGMENT OVERRIDE PREFIX
	opcds.push_back(new("\x2F", "das", A, BYTE, NONE) OPCD);

	opcds.push_back(new("\x30", "xor", RM, R, BYTE, MODREGRM) OPCD);
	opcds.push_back(new("\x31", "xor", RM, R, FULL, MODREGRM) OPCD);
	opcds.push_back(new("\x32", "xor", R, RM, BYTE, MODREGRM) OPCD);
	opcds.push_back(new("\x33", "xor", R, RM, FULL, MODREGRM) OPCD);
	opcds.push_back(new("\x34", "xor", A, IMM, BYTE, NONE) OPCD);
	opcds.push_back(new("\x35", "xor", A, IMM, FULL, NONE) OPCD);
	opcds.push_back(new("\x36", SS, SEGMENTPREFIX) OPCD); //SS SEGMENT OVERRIDE PREFIX
	opcds.push_back(new("\x37", "aaa", A, A, BYTE, NONE) OPCD);

	opcds.push_back(new("\x38", "cmp", RM, R, BYTE, MODREGRM) OPCD);
	opcds.push_back(new("\x39", "cmp", RM, R, FULL, MODREGRM) OPCD);
	opcds.push_back(new("\x3A", "cmp", R, RM, BYTE, MODREGRM) OPCD);
	opcds.push_back(new("\x3B", "cmp", R, RM, FULL, MODREGRM) OPCD);
	opcds.push_back(new("\x3C", "cmp", A, IMM, BYTE, NONE) OPCD);
	opcds.push_back(new("\x3D", "cmp", A, IMM, FULL, NONE) OPCD);
	opcds.push_back(new("\3E", DS, SEGMENTPREFIX) OPCD); //DS SEGMENT OVERRIDE PREFIX
	opcds.push_back(new("\x3F", "aas", A, A, BYTE, NONE) OPCD);

	opcds.push_back(new("\x40", "inc", A, FULL, NONE) OPCD);
	opcds.push_back(new("\x41", "inc", C, FULL, NONE) OPCD);
	opcds.push_back(new("\x42", "inc", D, FULL, NONE) OPCD);
	opcds.push_back(new("\x43", "inc", B, FULL, NONE) OPCD);
	opcds.push_back(new("\x44", "inc", SP, FULL, NONE) OPCD);
	opcds.push_back(new("\x45", "inc", BP, FULL, NONE) OPCD);
	opcds.push_back(new("\x46", "inc", SI, FULL, NONE) OPCD);
	opcds.push_back(new("\x47", "inc", DI, FULL, NONE) OPCD);

	opcds.push_back(new("\x48", "dec", A, FULL, NONE) OPCD);
	opcds.push_back(new("\x49", "dec", C, FULL, NONE) OPCD);
	opcds.push_back(new("\x4A", "dec", D, FULL, NONE) OPCD);
	opcds.push_back(new("\x4B", "dec", B, FULL, NONE) OPCD);
	opcds.push_back(new("\x4C", "dec", SP, FULL, NONE) OPCD);
	opcds.push_back(new("\x4D", "dec", BP, FULL, NONE) OPCD);
	opcds.push_back(new("\x4E", "dec", SI, FULL, NONE) OPCD);
	opcds.push_back(new("\x4F", "dec", DI, FULL, NONE) OPCD);

	opcds.push_back(new("\x50", "push", A, FULL, NONE) OPCD);
	opcds.push_back(new("\x51", "push", C, FULL, NONE) OPCD);
	opcds.push_back(new("\x52", "push", D, FULL, NONE) OPCD);
	opcds.push_back(new("\x53", "push", B, FULL, NONE) OPCD);
	opcds.push_back(new("\x54", "push", SP, FULL, NONE) OPCD);
	opcds.push_back(new("\x55", "push", BP, FULL, NONE) OPCD);
	opcds.push_back(new("\x56", "push", SI, FULL, NONE) OPCD);
	opcds.push_back(new("\x57", "push", DI, FULL, NONE) OPCD);

	opcds.push_back(new("\x58", "pop", A, FULL, NONE) OPCD);
	opcds.push_back(new("\x59", "pop", C, FULL, NONE) OPCD);
	opcds.push_back(new("\x5A", "pop", D, FULL, NONE) OPCD);
	opcds.push_back(new("\x5B", "pop", B, FULL, NONE) OPCD);
	opcds.push_back(new("\x5C", "pop", SP, FULL, NONE) OPCD);
	opcds.push_back(new("\x5D", "pop", BP, FULL, NONE) OPCD);
	opcds.push_back(new("\x5E", "pop", SI, FULL, NONE) OPCD);
	opcds.push_back(new("\x5F", "pop", DI, FULL, NONE) OPCD);

	opcds.push_back(new("\x69", "imul", R, M, IMM, FULL, MODREGRM) OPCD);
}

void Definition::InitExtendedOPCD() {
	extopcds.push_back(new("\x00", "sldt", RM, WORD, NONE) OPCD);
}

void* _OPCD::operator new(size_t stAllocateBlock, const char* value, int attributes) {
	LPOPCD p = (LPOPCD)malloc(stAllocateBlock);
	if (p) {
		p->value = value;
		p->attributes = attributes;
	}
	return p;
}

void* _OPCD::operator new(size_t stAllocateBlock, const char* value, char op1, int attributes) {
	LPOPCD p = (LPOPCD)malloc(stAllocateBlock);
	if (p) {
		p->value = value;
		p->opn = 1;
		p->ops = new char[1]{ op1 };
		p->attributes = attributes;
	}
	return p;
}

void* _OPCD::operator new(size_t stAllocateBlock, const char* value, const char* mnemonic, char op1, FORMAT format, int attributes) {
	LPOPCD p = (LPOPCD)malloc(stAllocateBlock);
	if (p) {
		p->value = value;
		p->mnemonic = mnemonic;
		p->opn = 1;
		p->ops = new char[1]{ op1 };
		p->format = format;
		p->attributes = attributes;
	}
	return p;
}

void* _OPCD::operator new(size_t stAllocateBlock, const char* value, const char* mnemonic, char op1, char op2, FORMAT format, int attributes) {
	LPOPCD p = (LPOPCD)malloc(stAllocateBlock);
	if (p) {
		p->value = value;
		p->mnemonic = mnemonic;
		p->opn = 2;
		p->ops = new char[2]{ op1, op2 };
		p->format = format;
		p->attributes = attributes;
	}
	return p;
}

void* _OPCD::operator new(size_t stAllocateBlock, const char* value, const char* mnemonic, char op1, char op2, char op3, FORMAT format, int attributes) {
	LPOPCD p = (LPOPCD)malloc(stAllocateBlock);
	if (p) {
		p->value = value;
		p->mnemonic = mnemonic;
		p->opn = 3;
		p->ops = new char[3]{ op1, op2, op3 };
		p->format = format;
		p->attributes = attributes;
	}
	return p;
}

void* _OPCD::operator new(size_t stAllocateBlock, const char* value, const char* mnemonic, char op1, char op2, char op3, char op4, FORMAT format, int attributes) {
	LPOPCD p = (LPOPCD)malloc(stAllocateBlock);
	if (p) {
		p->value = value;
		p->mnemonic = mnemonic;
		p->opn = 4;
		p->ops = new char[4]{ op1, op2, op3, op4 };
		p->format = format;
		p->attributes = attributes;
	}
	return p;
}