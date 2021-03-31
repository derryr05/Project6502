#include <iostream>
#include "../headers/CPU.h"
#include "../headers/Memory.h"

int main()
{
	CPU cpu;
	Memory memory;
	cpu.Reset(memory);

	// Machine code START ------------------------------
	memory.data[0xFFFC] = Instruction_STY_ZP;
	cpu.yRegister = 0x76;
	cpu.Execute(3, memory);
	// Machine code END --------------------------------
	
	std::cout << (int)memory.data[0x00] << std::endl;
	return 0;
}