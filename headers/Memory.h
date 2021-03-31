#pragma once

#include "Definitions.h"

class Memory
{
public:

	static constexpr DWord MAX_MEMORY = 1024 * 64;
	Byte data[MAX_MEMORY];

	void Initialise();

	Byte operator[](DWord address) const;

	void WriteWord(SignedDWord &clockCycle, Word value, DWord address);
};