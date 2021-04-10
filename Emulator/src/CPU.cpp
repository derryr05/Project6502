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
		{"BCC_REL", 0x90, 4}, {"BCS_REL", 0xB0, 4}, {"BEQ_REL", 0xF0, 4},
		{"BIT_ZP",  0x24, 3}, {"BIT_ABS", 0x2C, 4},
		{"BMI_REL", 0x30, 4},
		{"BNE_REL", 0xD0, 4},
		{"BPL_REL", 0x10, 4},
		{"BRK_IMM", 0x00, 7},
		{"BVC_REL", 0x50, 4},
		{"BVS_REL", 0x70, 4},
		{"CLC_IMM", 0x18, 2}, {"CLD_IMM", 0xD8, 2}, {"CLI_IMM", 0x58, 2}, {"CLV_IMM", 0xB8, 2},
		{"CMP_IMM", 0xC9, 2}, {"CMP_ZP", 0xC5, 3}, {"CMP_ZPX", 0xD5, 4}, {"CMP_ABS", 0xCD, 4}, {"CMP_ABX", 0xDD, 5}, {"CMP_ABY", 0xD9, 5}, {"CMP_INX", 0xC1, 6}, {"CMP_INY", 0xD1, 6},
		{"CPX_IMM", 0xE0, 2}, {"CPX_ZP", 0xE4, 3}, {"CPX_ABS", 0xEC, 4},
		{"CPY_IMM", 0xC0, 2}, {"CPY_ZP", 0xC4, 3}, {"CPY_ABS", 0xCC, 4},
		{"DEC_ZP",  0xC6, 5}, {"DEC_ZPX", 0xD6, 6}, {"DEC_ABS", 0xCE, 6}, {"DEC_ABX", 0xDE, 7},
		{"DEX_IMM", 0xCA, 2},
		{"DEY_IMM", 0x88, 2},
		{"EOR_IMM", 0x49, 2}, {"EOR_ZP", 0x45, 3}, {"EOR_ZPX", 0x55, 4}, {"EOR_ABS", 0x4D, 4}, {"EOR_ABX", 0x5D, 5}, {"EOR_ABY", 0x59, 5}, {"EOR_INX", 0x41, 6}, {"EOR_INY", 0x51, 6},
		{"INC_ZP",  0xE6, 5}, {"INC_ZPX", 0xF6, 6}, {"INC_ABS", 0xEE, 6}, {"INC_ABX", 0xFE, 7},
		{"INX_IMM", 0xE8, 2},
		{"INY_IMM", 0xC8, 2},
		{"JMP_ABS", 0x4C, 3}, {"JMP_IND", 0x6C, 5},
		{"JSR_ABS", 0x20, 6},
		{"LDA_IMM", 0xA9, 2}, {"LDA_ZP", 0xA5, 3}, {"LDA_ZPX", 0xB5, 4}, {"LDA_ABS", 0xAD, 4}, {"LDA_ABX", 0xBD, 5}, {"LDA_ABY", 0xB9, 5}, {"LDA_INX", 0xA1, 6}, {"LDA_INY", 0xB1, 6},
		{"LDX_IMM", 0xA2, 2}, {"LDX_ZP", 0xA6, 3}, {"LDX_ZPY", 0xB6, 4}, {"LDX_ABS", 0xAE, 4}, {"LDX_ABY", 0xBE, 5},
		{"LDY_IMM", 0xA0, 2}, {"LDY_ZP", 0xA4, 3}, {"LDY_ZPX", 0xB4, 4}, {"LDY_ABS", 0xAC, 4}, {"LDY_ABX", 0xBC, 5},
		{"LSR_ACC", 0x4A, 2}, {"LSR_ZP", 0x46, 5}, {"LSR_ZPX", 0x56, 6}, {"LSR_ABS", 0x4E, 6}, {"LSR_ABX", 0x5E, 7},
		{"NOP_IMM", 0xEA, 2},
		{"ORA_IMM", 0x09, 2}, {"ORA_ZP", 0x05, 3}, {"ORA_ZPX", 0x15, 4}, {"ORA_ABS", 0x0D, 4}, {"ORA_ABX", 0x1D, 5}, {"ORA_ABY", 0x19, 5}, {"ORA_INX", 0x01, 6}, {"ORA_INY", 0x11, 6},
		{"PHA_IMM", 0x48, 3},
		{"PHP_IMM", 0x08, 3},
		{"PLA_IMM", 0x68, 4},
		{"PLP_IMM", 0x28, 4},
		{"ROL_ACC", 0x2A, 2}, {"ROL_ZP", 0x26, 5}, {"ROL_ZPX", 0x36, 6}, {"ROL_ABS", 0x2E, 6}, {"ROL_ABX", 0x3E, 6},
		{"ROR_ACC", 0x6A, 2}, {"ROR_ZP", 0x66, 5}, {"ROR_ZPX", 0x76, 6}, {"ROR_ABS", 0x6E, 6}, {"ROR_ABX", 0x7E, 7},
		{"RTI_IMM", 0x40, 6},
		{"RTS_IMM", 0x60, 6},
		{"SBC_IMM", 0xE9, 2}, {"SBC_ZP", 0xE5, 3},
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