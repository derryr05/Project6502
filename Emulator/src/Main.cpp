#include <iostream>
#include <string>
#include "../headers/CPU.h"
#include "../headers/Memory.h"

CPU cpu;
Memory memory;

void PrintFinalOutput();

int main()
{
	cpu.Reset(memory);

	// Storing value of X Register into Memory Address 0xABCD
	memory.data[0xFFFC] = cpu.opcode[8].opcodeValue;
	memory.data[0xFFFD] = 0xCD;
	memory.data[0xFFFE] = 0xAB;

	cpu.xRegister = 0x91;

	// memory.data[0xFFFE] = Instruction_STA_ZP;
	cpu.Execute(cpu.opcode[8].clockCycle, memory);

	std::cout << "Memory address[0xABCD]: " << std::hex << (int)memory.data[0xABCD] << std::endl;
	PrintFinalOutput();

	return 0;
}

void PrintFinalOutput()
{
	std::cout << "\nRegister Status:" << std::endl;
	std::cout << "Accumulator     = 0x" << std::hex << (int)cpu.accumulator << std::endl;
	std::cout << "X Register      = 0x" << std::hex << (int)cpu.xRegister << std::endl;
	std::cout << "Y Register      = 0x" << std::hex << (int)cpu.yRegister << std::endl;
	std::cout << "Stack Pointer   = 0x" << std::hex << (int)cpu.stackPointer << std::endl;
	std::cout << "Program Counter = 0x" << std::hex << (int)cpu.programCounter << std::endl;

	std::cout << "\nFlag Status:" << std::endl;
	std::cout << "Carry             = " << (int)cpu.carry << std::endl;
	std::cout << "Zero              = " << (int)cpu.zero << std::endl;
	std::cout << "Interrupt Disable = " << (int)cpu.interruptDisable << std::endl;
	std::cout << "Decimal           = " << (int)cpu.decimal << std::endl;
	std::cout << "Break             = " << (int)cpu.break_ << std::endl;
	std::cout << "Overflow          = " << (int)cpu.overflow << std::endl;
	std::cout << "Negative          = " << (int)cpu.negative << std::endl;
}