#include <iostream>
#include "../headers/CPU.h"
#include "../headers/Memory.h"

int main()
{
	CPU cpu;
	Memory memory;
	cpu.Reset(memory);

	// Assembly code START ------------------------------
	memory.data[0xFFFC] = Instruction_LDA_ZPX;
	cpu.xRegister = 0xFF;
	memory.data[0x00FF] = 0x21;
	cpu.Execute(4, memory);
	// Assembly code END --------------------------------
	
	std::cout << (int)cpu.accumulator << std::endl;
	return 0;
}