#pragma once
#include "sib.h"
#include "definition.h"

#define MODRM_MOD_MASK 0xC0
#define MODRM_REG_MASK 0x38
#define MODRM_RM_MASK 0x7

#define MODRM_REG_INDIRECT_ADDRESSING 0
#define MODRM_SIB_NO_DISPLACEMENT 1
#define MODRM_DISPLACEMENT_ONLY 2
#define MODRM_BYTE_SIGNED_DISPLACEMENT 3
#define MODRM_DWORD_SIGNED_DISPLACEMENT 4
#define MODRM_REG_ONLY_ADRESSING 5

typedef struct _MODRM {
public:
	_MODRM(char* p, int s);

	std::string RegToString();
	std::string RMToString();
	const char* GetRegister(int index);

	int GetAdressingMode();
	int Length();
	
	char GetMod();
	char GetReg();
	char GetRM();

	int HasSIB();
	int IsValid();
private:
	SIB GetSIB();
	char* p;
	char s;
	const char* REGISTER[8][3] = {
		{"al", "ax", "eax"},
		{"cl", "cx", "ecx"},
		{"dl", "dx", "edx"},
		{"bl", "bx", "ebx"},
		{"ah", "sp", "esp"},
		{"ch", "bp", "ebp"},
		{"dh", "si", "esi"},
		{"bh", "di", "edi"}
	};
	const char* ptrString[3] = { "PTR BYTE", "PTR WORD", "PTR DWORD" };
}MODRM, * LPMODRM;