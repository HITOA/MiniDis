#include "instruction.h"

Instruction::Instruction(char* p, Definition* d) {
	this->p = p;
	opCode = new(p, d) OPCODE;
}

std::string Instruction::ToString() {
	std::stringstream out;
	if (opCode->IsValid()) {
		MODRM modrm(&p[opCode->Length()], opCode->GetOprSize());
		LPOPCD lpOPCD = opCode->GetOpCodeDefinition();

		if (opCode->HasModRMByte() && !modrm.IsValid())
			return "(bad)";

		out << opCode->GetMnemonic() << " ";

		int offset = 0;

		if (opCode->HasModRMByte())
			offset += modrm.Length();

		for (int i = 0; i < lpOPCD->opn; i++) {
			int operand = lpOPCD->ops[i];
			if (operand >= 0 && operand <= 8)
				out << modrm.GetRegister(operand - 1);
			switch (operand) {
			case R:
				out << modrm.RegToString();
				break;
			case M:
				out << modrm.RMToString();
				break;
			case RM:
				out << modrm.RMToString();
				break;
			case IMM:
				offset += ParseIMM(&p[opCode->Length() + offset], opCode->GetOprSize(), &out);
				break;
			default:
				break;
			}
			if (i != lpOPCD->opn - 1) {
				out << ", ";
			}
		}
	}
	else {
		out << "(bad)";
	}
	return out.str();
}

int Instruction::ParseIMM(char* p, int s, std::stringstream* out) {
	
	if (s == 0) {
		*out << "0x"
			<< std::hex << (unsigned)(p[0]);
		return 1;
	}
	if (s == 1) {
		*out << "0x"
			<< std::hex << *((short*)p);
		return 2;
	}
	if (s == 2) {
		*out << "0x"
			<< std::hex << *((int*)p);
		return 4;
	}
	return 0;
}