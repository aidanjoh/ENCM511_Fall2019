/*
 * ReadCycles_ASM.asm
 *
 *  Created on: Oct 7, 2018
 *      Author: smithmr
 */

 	.section program;
 	.global _ReadCycles_ASM;
 _ReadCycles_ASM:
 	nop; nop; nop; nop;  // Stop assembler warning messages
 
 	R0 = CYCLES; 
 _ReadCycles_ASM.END:	
 	RTS;