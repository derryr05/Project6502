#include <iostream>
#include <string>
#include <vector>
#include "../headers/CPU.h"

void CPU::OpcodeInitialise()
{
	opcode =
	{
		{"ADC_IMM", 0x69, 2}, {"ADC_ZP", 0x65, 3}, {"ADC_ZPX", 0x75, 4}, {"ADC_ABS", 0x6D, 4}, {"ADC_ABX", 0x7D, 5}, {"ADC_ABY", 0x79, 5}, {"ADC_INX", 0x61, 6}, {"ADC_INY", 0x71, 6},
		{"AND_IMM", 0x29, 2}, {"AND_ZP", 0x25, 3}, {"AND_ZPX", 0x35, 4}, {"AND_ABS", 0x2D, 4}, {"AND_ABX", 0x3D, 5}, {"AND_ABY", 0x39, 5}, {"AND_INX", 0x21, 6}, {"AND_INY", 0x31, 6},
		{"ASL_ACC", 0x0A, 2}, {"ASL_ZP", 0x06, 5}, {"ASL_ZPX", 0x16, 6}, {"ASL_ABS", 0x0E, 6}, {"ASL_ABX", 0x1E, 7},
		{"BIT_ZP",  0x24, 3}, {"BIT_ABS", 0x2C, 4},
		{"BRK_IMM", 0x00, 7},
		{"CMP_IMM", 0xC9, 2}, {"CMP_ZP", 0xC5, 3}, {"CMP_ZPX", 0xD5, 4}, {"CMP_ABS", 0xCD, 4}, {"CMP_ABX", 0xDD, 5}, {"CMP_ABY", 0xD9, 5}, {"CMP_INX", 0xC1, 6}, {"CMP_INY", 0xD1, 6},
		{"STX_ABS", 0x8E, 4}
	};
}

void CPU::Reset(Memory &memory)
{
	OpcodeInitialise();
	programCounter = 0xFFFC;
	stackPointer = 0x0100;
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
	case Instruction_STX_ABS:
	{
		std::cout << "STX" << " ";
		Word address = AbsAddress(clockCycle, memory);
		int i = address;
		std::cout << "#$" << std::hex << std::uppercase << i << std::endl;
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
	case Instruction_STY_ABS:
	{
		std::cout << "STY" << " ";
		Word address = AbsAddress(clockCycle, memory);
		int i = address;
		std::cout << "#$" << std::hex << std::uppercase << i << std::endl;
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

Word CPU::AbsAddress(SignedDWord& clockCycle, const Memory& memory)
{
	Word address = FetchWord(clockCycle, memory);
	return address;
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