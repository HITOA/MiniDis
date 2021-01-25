#include "modrm.h"

_MODRM::_MODRM(char* p, int s) {
	this->p = p;
	this->s = s;
}

std::string _MODRM::RegToString() {
	return REGISTER[GetReg()][s];
}

std::string _MODRM::RMToString() {
	std::stringstream out;
	switch (GetAdressingMode())
	{
	case MODRM_SIB_NO_DISPLACEMENT:
		out << ptrString[s] << " [" << GetSIB().ToString() << "]";
		break;
	case MODRM_DISPLACEMENT_ONLY:
		out << ptrString[s] << " ds:"
			<< "0x"
			<< std::hex << *((int*)&p[1]);
		break;
	case MODRM_REG_INDIRECT_ADDRESSING:
		out << ptrString[s] << " [" << REGISTER[GetRM()][2] << "]";
		break;
	case MODRM_BYTE_SIGNED_DISPLACEMENT:
		out << ptrString[s] << " [" << REGISTER[GetRM()][2];
		if (*((signed char*)&p[1]) >= 0)
			out << " + ";
		if (*((signed char*)&p[1]) < 0)
			out << " - ";
		out << "0x"
			<< std::hex << abs(*((signed char*)&p[1]))
			<< "]";
		break;
	case MODRM_DWORD_SIGNED_DISPLACEMENT:
		out << ptrString[s] << " [" << REGISTER[GetRM()][2];
		if (*((int*)&p[1]) >= 0)
			out << " + ";
		if (*((int*)&p[1]) < 0)
			out << " - ";
		out << "0x"
			<< std::hex << abs(*((int*)&p[1]))
			<< "]";
		break;
	default:
		out << REGISTER[GetRM()][s];
		break;
	}
	return out.str();
}

const char* _MODRM::GetRegister(int index) {
	return REGISTER[index][s];
}

int _MODRM::GetAdressingMode() {
	if (GetMod() == 0) {
		if (GetRM() == 4)
			return MODRM_SIB_NO_DISPLACEMENT;
		if (GetRM() == 5)
			return MODRM_DISPLACEMENT_ONLY;
		return MODRM_REG_INDIRECT_ADDRESSING;
	}
	if (GetMod() == 1)
		return MODRM_BYTE_SIGNED_DISPLACEMENT;
	if (GetMod() == 2)
		return MODRM_DWORD_SIGNED_DISPLACEMENT;
	return MODRM_REG_ONLY_ADRESSING;
}

int _MODRM::Length() {
	switch (GetAdressingMode())
	{
	case MODRM_SIB_NO_DISPLACEMENT:
		return 1 + GetSIB().Length();
	case MODRM_DISPLACEMENT_ONLY:
		return 5;
	case MODRM_REG_INDIRECT_ADDRESSING:
		return 1;
	case MODRM_BYTE_SIGNED_DISPLACEMENT:
		return 2;
	case MODRM_DWORD_SIGNED_DISPLACEMENT:
		return 5;
	default:
		return 1;
	}
}

char _MODRM::GetMod() {
	return (this->p[0] & MODRM_MOD_MASK) >> 6;
}

char _MODRM::GetReg() {
	return (this->p[0] & MODRM_REG_MASK) >> 3;
}

char _MODRM::GetRM() {
	return this->p[0] & MODRM_RM_MASK;
}

int _MODRM::HasSIB() {
	if (GetMod() == 0 && GetRM() == 4) {
		return 1;
	}
	return 0;
}

int _MODRM::IsValid() {
	if (GetMod() == 0 && GetRM() == 4) {
		if (!GetSIB().IsValid())
			return 0;
	}
	return 1;
}

SIB _MODRM::GetSIB() {
	return SIB(&p[1]);
}