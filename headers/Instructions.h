#pragma once

#include "Definitions.h"

static constexpr Byte
	Instruction_ADC_IMM = 0x69,
	Instruction_ADC_ZP  = 0x65,
	Instruction_ADC_ZPC = 0x75,
	Instruction_ADC_ABS = 0x6D,
	Instruction_ADC_ABX = 0x7D,
	Instruction_ADC_INX = 0x61,
	Instruction_ADC_INY = 0x71,
	Instruction_AND_IMM = 0x29, // Complete
	Instruction_CMP_IMM = 0xC9,
	Instruction_JSR_ABS = 0x20, // Complete
	Instruction_LDA_IMM = 0xA9, // Complete
	Instruction_LDA_ZP  = 0xA5, // Complete
	Instruction_LDX_IMM = 0xA2, // Complete
	Instruction_LDX_ZP  = 0xA6,
	Instruction_LDY_IMM = 0xA0, // Complete
	Instruction_LDY_ZP  = 0xA4,
	Instruction_STA_ZP  = 0x85, // Complete
	Instruction_STA_ZPX = 0x95, 
	Instruction_STA_ABS = 0x8D, 
	Instruction_STX_ZP  = 0x86, // Complete
	Instruction_STY_ZP  = 0x84; // Complete