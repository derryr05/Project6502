#include <iostream>
#include <string>

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
		std::cout << "AND" << " ";
		Byte value = FetchByte(clockCycle, memory);
		int i = value;
		std::cout << "#$" << std::hex << std::uppercase << i << std::endl;
		accumulator = (accumulator & value);
		LDA_ANDSetFlagStatus();
	} break;
	case Instruction_JSR_ABS:
	{
		std::cout << "JSR" << " ";
		Word routineAddress = FetchWord(clockCycle, memory);
		int i = routineAddress;
		std::cout << "#$" << std::hex << std::uppercase << i << std::endl;
		memory.WriteWord(clockCycle, programCounter - 1, stackPointer);
		clockCycle--;
		programCounter = routineAddress;
		clockCycle--;
	} break;
	case Instruction_LDA_IMM:
	{
		std::cout << "LDA" << " ";
		Byte value = FetchByte(clockCycle, memory);
		int i = value;
		std::cout << "#$" << std::hex << std::uppercase << i << std::endl;
		accumulator = value;
		LDA_ANDSetFlagStatus();
	} break;
	case Instruction_LDA_ZP:
	{
		std::cout << "LDA" << " ";
		Byte address = ZeroPageAddress(clockCycle, memory);
		int i = address;
		std::cout << "#$" << std::hex << std::uppercase << i << std::endl;
		accumulator = ReadByteAtAddress(clockCycle, address, memory);
		LDA_ANDSetFlagStatus();
	} break;
	case Instruction_LDA_ZPX:
	{
		std::cout << "LDA" << " ";
		Byte address = ZeroPageAddress(clockCycle, memory);
		int i = address;
		std::cout << "#$" << std::hex << std::uppercase << i << ",X" << std::endl;
		address += xRegister;
		clockCycle--;
		accumulator = ReadByteAtAddress(clockCycle, address, memory);
		LDA_ANDSetFlagStatus();
	} break;
	case Instruction_LDX_IMM: 
	{
		std::cout << "LDX" << " ";
		Byte value = FetchByte(clockCycle, memory);
		int i = value;
		std::cout << "#$" << std::hex << std::uppercase << i << std::endl;
		xRegister = value;
		LDXSetFlagStatus();
	} break;
	case Instruction_LDX_ZP: 
	{
		std::cout << "LDX" << " ";
		Byte address = ZeroPageAddress(clockCycle, memory);
		int i = address;
		std::cout << "#$" << std::hex << std::uppercase << i << std::endl;
		xRegister = ReadByteAtAddress(clockCycle, address, memory);
		LDXSetFlagStatus();
	} break;
	case Instruction_LDY_IMM: 
	{
		std::cout << "LDY" << " ";
		Byte value = FetchByte(clockCycle, memory);
		int i = value;
		std::cout << "#$" << std::hex << std::uppercase << i << std::endl;
		yRegister = value;
		LDYSetFlagStatus();
	} break;
	case Instruction_LDY_ZP:
	{
		std::cout << "LDY" << " ";
		Byte address = ZeroPageAddress(clockCycle, memory);
		int i = address;
		std::cout << "#$" << std::hex << std::uppercase << i << std::endl;
		yRegister = ReadByteAtAddress(clockCycle, address, memory);
		LDYSetFlagStatus();
	} break;
	case Instruction_NOP_IMP:
	{
		std::cout << "NOP" << std::endl;
		clockCycle--;
	} break;
	case Instruction_STA_ZP:
	{
		std::cout << "STA" << " ";
		Word address = ZeroPageAddress(clockCycle, memory);
		int i = address;
		std::cout << "#$" << std::hex << std::uppercase << i << std::endl;
		WriteByteAtAddress(accumulator, clockCycle, address, memory);
	} break;
	case Instruction_STA_ZPX:
	{
		std::cout << "STA" << " ";
		Byte address = ZeroPageAddress(clockCycle, memory);
		int i = address;
		std::cout << "#$" << std::hex << std::uppercase << i << ",X" << std::endl;
		address += xRegister;
		clockCycle--;
		WriteByteAtAddress(accumulator, clockCycle, address, memory);
	} break;
	case Instruction_STX_ZP:
	{
		std::cout << "STX" << " ";
		Word address = ZeroPageAddress(clockCycle, memory);
		int i = address;
		std::cout << "#$" << std::hex << std::uppercase << i << std::endl;
		WriteByteAtAddress(xRegister, clockCycle, address, memory);
	} break;
	case Instruction_STX_ZPY:
	{
		std::cout << "STX" << " ";
		Byte address = ZeroPageAddress(clockCycle, memory);
		int i = address;
		std::cout << "#$" << std::hex << std::uppercase << i << ",Y" << std::endl;
		address += yRegister;
		clockCycle--;
		WriteByteAtAddress(xRegister, clockCycle, address, memory);
	} break;
	case Instruction_STY_ZP:
	{
		std::cout << "STY" << " ";
		Word address = ZeroPageAddress(clockCycle, memory);
		int i = address;
		std::cout << "#$" << std::hex << std::uppercase << i << std::endl;
		WriteByteAtAddress(yRegister, clockCycle, address, memory);
	} break;
	case Instruction_STY_ZPX:
	{
		std::cout << "STY" << " ";
		Byte address = ZeroPageAddress(clockCycle, memory);
		int i = address;
		std::cout << "#$" << std::hex << std::uppercase << i << ",X" << std::endl;
		address += xRegister;
		clockCycle--;
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