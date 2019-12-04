/*
 * Idle_WaitForInterrupts_ASM.asm
 *
 *  Created on: Oct 7, 2018
 *      Author: smithmr
 */

  	.section program;
 	.global _Idle_WaitForInterrupts_ASM;
_Idle_WaitForInterrupts_ASM:
 	nop; nop; nop; nop;  // Stop assembler warning messages
 
 	idle; 
_Idle_WaitForInterrupts_ASM.END:	
 	RTS;
 	