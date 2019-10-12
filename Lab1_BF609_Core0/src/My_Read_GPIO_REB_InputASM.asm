/*
 * My_Read_GPIO_REB_InputASM.asm
 *
 *  Created on: Oct 12, 2019
 *      Author: aidan
 */
#include <blackfin.h>
#include "Lab1_BF609_Core0.h"

	.section L1_data;
	
	.section program;
	.global _My_Read_GPIO_REB_InputASM;

	#define returnValue_R0 R0
	
_My_Read_GPIO_REB_InputASM:
	LINK 20;
	
	R1 = MASK_KEEP_BITS_11_TO_8; //Putting the masks into the registers
	
	//This code is storing the value in the port F register into the pointer register P0
	P0.L = lo(REG_PORTF_DATA);
	P0.H = hi(REG_PORTF_DATA);
	
	returnValue_R0 = W[P0](Z); //Putting the value for the switches into the R0 register (this is reading the values)

	returnValue_R0 = returnValue_R0 & R1; //This is selecting only bits 11-8 which are the input pins
	returnValue_R0 = returnValue_R0 >> 8; //Shifting the 4bit input down to the bottom to be able to read as a switche value
	
	UNLINK;

_My_Read_GPIO_REB_InputASM.END:
	RTS;
	