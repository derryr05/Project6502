#include "../headers/Definitions.h"
#include "../headers/Memory.h"

// Initialise memory to 0
void Memory::Initialise()
{
	for (DWord i = 0; i < Memory::MAX_MEMORY; i++)
	{
		Memory::data[i] = 0;
	}
}

Byte Memory::operator[](DWord address) const
{
	return Memory::data[address];
}

void Memory::WriteWord(SignedDWord &clockCycle, Word value, DWord address)
{
	data[address] = value & 0xFF;
	data[address + 1] = (value >> 8);
	clockCycle -= 2;
}
