/*
 * My_Init_GPIO_REB_InputASM.asm
 *
 *  Created on: Oct 12, 2019
 *      Author: aidan
 */
#include <blackfin.h>

	.section L1_data;
	
	.section program;
	.global _My_Init_GPIO_REB_InputASM;

	#define returnValue_R0 R0
	#define MASK_KEEP_BITS_11_TO_8 0x0f00
	
_My_Init_GPIO_REB_InputASM:
	LINK 20;
	
	//This code is storing the value in the port F data register into the pointer register P0
	P0.L = lo(REG_PORTF_DATA);
	P0.H = hi(REG_PORTF_DATA);
	
	R1 = 0x0000;
	[P0] = R1; //This is intializing the data register with all zeros to begin with
	
	R1 = 0x0f00;
	
	R2 = 0xf0ff(Z);
	
	//This code is storing the value in the port F enabled register into the pointer register P0
	P0.L = lo(REG_PORTF_INEN);
	P0.H = hi(REG_PORTF_INEN);
	
	R3 = W[P0](Z);
	R0 = R3 & R2; //This is making sure we only zero the bits 11-8
	[P0] = R0;
	
	R3 = W[P0](Z);

	R0 = R3 | R1; //This putting in the correct enabled values into the enabled bits part
	[P0] = R0;
	
	//This code is storing the value in the port F polarity register into the pointer register P0
	P0.L = lo(REG_PORTF_POL);
	P0.H = hi(REG_PORTF_POL);
	
	R1 = 0x0000;
	[P0] = R1;
	
	UNLINK;

_My_Init_GPIO_REB_InputASM.END:
	RTS;
	