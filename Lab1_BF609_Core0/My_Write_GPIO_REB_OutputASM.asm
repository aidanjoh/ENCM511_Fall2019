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
	
_My_Write_GPIO_OutputASM:
	LINK 20;
	
	R1 = 12;
	returnValue_R0 = returnValue_R0 << R1;
	PORTF_DATA = returnValue_RO;
	
	UNLINK;

_My_Write_GPIO_OutputASM.END:
	RTS;
