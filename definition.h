#pragma once
#include <malloc.h>
#include <vector>

#define NINT 252

#define NONE 0

#define MODREGRM       (0x0001)
#define OPCREG         (0x0002)
#define TBOPCPREFIX    (0x0004)
#define SEGMENTPREFIX  (0x0008)

//General Register
#define A 1
#define C 2
#define D 3
#define B 4
#define SP 5
#define BP 6
#define SI 7
#define DI 8
//Operand Type
#define R 9
#define M 10
#define RM 11
#define IMM 12
#define REL 13
//Segment
#define ES 14
#define CS 15
#define SS 16
#define DS 17
#define FS 18
#define GS 19
//Size
#define BYTE 1
#define WORD 2
#define DWORD 3
#define ANY 4
#define FULL WORD + DWORD

typedef char FORMAT;

typedef class _OPCD {
public:
	void* operator new(size_t stAllocateBlock, const char* value, int attributes);

	void* operator new(size_t stAllocateBlock, const char* value, char op1, int attributes);

	void* operator new(size_t stAllocateBlock, const char* value, const char* mnemonic, char op1, FORMAT format, int attributes);

	void* operator new(size_t stAllocateBlock, const char* value, const char* mnemonic, char op1, char op2, FORMAT format, int attributes);

	void* operator new(size_t stAllocateBlock, const char* value, const char* mnemonic, char op1, char op2, char op3, FORMAT format, int attributes);

	void* operator new(size_t stAllocateBlock, const char* value, const char* mnemonic, char op1, char op2, char op3, char op4, FORMAT format, int attributes);

	const char* value;
	const char* mnemonic;
	char opn;
	char* ops;
	FORMAT format;
	int attributes;
}OPCD, *LPOPCD;

class Definition {
public:
	Definition();
	LPOPCD GetFirstByte(char b);
	LPOPCD GetExtendedByte(char b);
private:
	void InitOPCD();
	void InitExtendedOPCD();
	std::vector<LPOPCD> opcds;
	std::vector<LPOPCD> extopcds;
};