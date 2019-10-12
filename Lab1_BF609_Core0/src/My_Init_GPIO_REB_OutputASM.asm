/*
 * My_Init_GPIO_REB_OutputASM.asm
 *
 *  Created on: Oct 12, 2019
 *      Author: aidan
 */
#include <blackfin.h>

	.section L1_data;
	
	.section program;
	.global _My_Init_GPIO_REB_OutputASM;

	#define returnValue_R0 R0
	#define MASK_KEEP_BITS_11_TO_0 0x0fff
	
_My_Init_GPIO_REB_OutputASM:
	LINK 20;
	
	//This code is storing the value in the port F data register into the pointer register P0
	P0.L = lo(REG_PORTF_DIR);
	P0.H = hi(REG_PORTF_DIR);
	
	R0 = W[P0](Z);
	R1 = MASK_KEEP_BITS_11_TO_0;
	R2 = 0xf000(Z);
	
	R0 = R0 & R1;
	R0 = R0 | R2;
	
	[P0] = R0;
	
	UNLINK;

_My_Init_GPIO_REB_OutputASM.END:
	RTS;
	