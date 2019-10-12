/*
 * My_Write_GPIO_REB_OutputASM.asm
 *
 *  Created on: Oct 11, 2019
 *      Author: aidan
 */
 
#include <blackfin.h>

	.section L1_data;
	
	.section program;
	.global _My_Write_GPIO_OutputASM;

	#define returnValue_R0 R0
	#define MaskBitValues11to0 0x0fff
	
_My_Write_GPIO_OutputASM:
	LINK 20;
	
	R1 = MaskBitValues11to0;
	P0.L = lo(REG_PORTF_DATA);
	P0.h = hi(REG_PORTF_DATA);
	
	R2 = W[P0](Z);
	R3 = MaskBitValues11to0;
	
	returnValue_R0 = returnValue_R0 << 12;
	
	R2 = R2 & R3;
	
	returnValue_R0 = returnValue_R0 | R2;
	
	P0 = returnValue_R0;
	
	UNLINK;

_My_Write_GPIO_OutputASM.END:
	RTS;
