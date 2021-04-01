#include <iostream>
#include "../headers/CPU.h"
#include "../headers/Memory.h"

int main()
{
	CPU cpu;
	Memory memory;
	cpu.Reset(memory);

	// Assembly code START ------------------------------
	memory.data[0xFFFC] = Instruction_NOP_IMP;
	memory.data[0xFFFD] = Instruction_LDA_IMM;
	memory.data[0xFFFE] = 0x82;
	cpu.Execute(4, memory);
	// Assembly code END --------------------------------
	
	std::cout << (int)cpu.accumulator << std::endl;
	return 0;
}