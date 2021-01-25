#include "sib.h"

_SIB::_SIB(char* p) {
	this->p = p;
}

std::string _SIB::ToString() {
	std::stringstream out;
	if (GetBase() == 5) {
		int disp = *((int*)&p[1]);

		out << REGISTER[GetIndex()]
			<< " * "
			<< SCALEVALUE[GetScale()];
		if (disp >= 0)
			out << " + ";
		if (disp < 0)
			out << " - ";
		out << "0x"
			<< std::hex << abs(disp);

	}
	else {
		out << REGISTER[GetBase()]
			<< " + "
			<< REGISTER[GetIndex()]
			<< " * "
			<< SCALEVALUE[GetScale()];
	}
	return out.str();
}

int _SIB::Length() {
	if (GetBase() == 5)
		return 5;
	return 1;
}

char _SIB::GetScale() {
	return (this->p[0] & SIB_SCALE_MASK) >> 6;
}

char _SIB::GetIndex() {
	return (this->p[0] & SIB_INDEX_MASK) >> 3;
}

char _SIB::GetBase() {
	return this->p[0] & SIB_BASE_MASK;
}

int _SIB::IsValid() {
	if (GetIndex() == 4)
		return 0;
	return 1;
}