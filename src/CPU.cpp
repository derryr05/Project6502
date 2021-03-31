#include <stdio.h>
#include "../headers/CPU.h"

void CPU::Reset(Memory &memory)
{
	programCounter = 0xFFFC;
	stackPointer = 0x100;
	carry = zero = interruptDisable = decimal = break_ = overflow = negative = 0;
	accumulator = xRegister = yRegister = 0;
	memory.Initialise();
}

Byte CPU::FetchByte(SignedDWord& clockCycle, const Memory& memory)
{
	Byte data = memory[programCounter];
	programCounter++;
	clockCycle--;
	return data;
}

Word CPU::FetchWord(SignedDWord& clockCycle, const Memory& memory)
{
	Word data = memory[programCounter];
	programCounter++;
	data |= (memory[programCounter] << 8);
	programCounter++;
	clockCycle-=2;
	return data;
}

Byte CPU::ReadByteAtAddress(SignedDWord& clockCycle, Byte address, const Memory& memory)
{
	Byte data = memory[address];
	clockCycle--;
	return data;
}

void CPU::WriteByteAtAddress(Byte value, SignedDWord &clockCycle, Word address, Memory& memory)
{
	memory.data[address] = value;
	clockCycle--;
}

void CPU::Execute(SignedDWord clockCycle, Memory& memory)
{
	while (clockCycle > 0)
	{
		SwitchInstruction(clockCycle, memory);
	}
}

void CPU::SwitchInstruction(SignedDWord& clockCycle, Memory& memory)
{
	Byte instruction = FetchByte(clockCycle, memory);
	switch (instruction)
	{
	case Instruction_AND_IMM:
	{
		Byte value = FetchByte(clockCycle, memory);
		accumulator = (accumulator & value);
		LDA_ANDSetFlagStatus();
	} break;
	case Instruction_JSR_ABS:
	{
		Word routineAddress = FetchWord(clockCycle, memory);
		memory.WriteWord(clockCycle, programCounter - 1, stackPointer);
		clockCycle--;
		programCounter = routineAddress;
		clockCycle--;
	} break;
	case Instruction_LDA_IMM:
	{
		Byte value = FetchByte(clockCycle, memory);
		accumulator = value;
		LDA_ANDSetFlagStatus();
	} break;
	case Instruction_LDA_ZP:
	{
		Byte address = FetchByte(clockCycle, memory);
		accumulator = ReadByteAtAddress(clockCycle, address, memory);
		LDA_ANDSetFlagStatus();
	} break;
	case Instruction_LDX_IMM:
	{
		Byte address = FetchByte(clockCycle, memory);
		xRegister = ReadByteAtAddress(clockCycle, address, memory);
		LDXSetFlagStatus();
	} break;
	case Instruction_LDX_ZP: // TODO
	{
		Word address = ZeroPageAddress(clockCycle, memory);
		WriteByteAtAddress(xRegister, clockCycle, address, memory);
	} break;
	case Instruction_LDY_IMM:
	{
		Byte address = FetchByte(clockCycle, memory);
		yRegister = ReadByteAtAddress(clockCycle, address, memory);
		LDYSetFlagStatus();
	} break;
	case Instruction_STA_ZP:
	{
		Word address = ZeroPageAddress(clockCycle, memory);
		WriteByteAtAddress(accumulator, clockCycle, address, memory);
	} break;
	case Instruction_STX_ZP:
	{
		Word address = ZeroPageAddress(clockCycle, memory);
		WriteByteAtAddress(xRegister, clockCycle, address, memory);
	} break;
	case Instruction_STY_ZP:
	{
		Word address = ZeroPageAddress(clockCycle, memory);
		WriteByteAtAddress(yRegister, clockCycle, address, memory);
	} break;
	default:
		printf("Instruction not supported");
	}
	return;
}

Word CPU::ZeroPageAddress(SignedDWord& clockCycle, const Memory& memory)
{
	Byte zeroPageAddr = FetchByte(clockCycle, memory);
	return zeroPageAddr;
}

void CPU::LDA_ANDSetFlagStatus()
{
	zero = (accumulator == 0);
	negative = (accumulator & 0b10000000) > 0;
}

void CPU::LDXSetFlagStatus()
{
	zero = (accumulator == 0);
	negative = (xRegister & 0b10000000) > 0;
}

void CPU::LDYSetFlagStatus()
{
	zero = (accumulator == 0);
	negative = (yRegister & 0b10000000) > 0;
}