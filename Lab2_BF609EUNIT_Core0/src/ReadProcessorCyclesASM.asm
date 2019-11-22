/*
 * ReadProcessorCyclesASM.asm
 *
 *  Created on: Sep 26, 2019
 *      Author: aidan
 */
	.section L1_data;
	
	.section program;
	.global _ReadProcessorCyclesASM;
	
	#define returnValue_R0 R0
	#define returnValue_R1 R1
	
_ReadProcessorCyclesASM:
	LINK 20;
	
	returnValue_R0 = CYCLES;
	returnValue_R1 = CYCLES2;
	
	UNLINK;

_ReadProcessorCyclesASM.END:
	RTS;