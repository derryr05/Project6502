#pragma once

#include "Definitions.h"
#include "Memory.h"
#include "Instructions.h"
#include <vector>

class CPU
{
public:
	// -------- REGISTERS -------- //
	Word programCounter;
	Byte stackPointer;

	Byte accumulator, xRegister, yRegister;

	// ---------- FLAGS ---------- //
	Byte carry : 1;
	Byte zero : 1;
	Byte interruptDisable : 1;
	Byte decimal : 1;
	Byte break_ : 1;
	Byte overflow : 1;
	Byte negative : 1;

	// Stores all instructions along with their clock cycles
	std::vector<Instruction> opcode;

	void OpcodeInitialise();

	void Reset(Memory &memory);

	Byte FetchByte(SignedDWord& clockCycle, const Memory &memory);

	Word FetchWord(SignedDWord& clockCycle, const Memory &memory);

	Byte ReadByteAtAddress(SignedDWord& clockCycle, Byte address, const Memory &memory);

	void WriteByteAtAddress(Byte value, SignedDWord &clockCycle, Word address, Memory &memory);

	void Execute(SignedDWord clockCycle, Memory &memory);

	void SwitchInstruction(SignedDWord& clockCycle, Memory &memory);

	void LDA_ANDSetFlagStatus();

	void LDXSetFlagStatus();

	void LDYSetFlagStatus();

	// Addressing modes
	Word ZeroPageAddress(SignedDWord& clockCycle, const Memory& memory);

	Word AbsAddress(SignedDWord& clockCycle, const Memory& memory);
};