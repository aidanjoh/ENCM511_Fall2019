/*
 * My_Write_GPIO_REB_OutputASM.asm
 *
 *  Created on: Oct 11, 2019
 *      Author: aidan
 */
 
#include <blackfin.h>

	.section L1_data;
	
	.section program;
	.global _My_Write_GPIO_REB_OutputASM;

	#define returnValue_R0 R0
	#define MaskBitValues11to0 0x0fff
	
_My_Write_GPIO_REB_OutputASM:
	LINK 20;
	
	R1 = MaskBitValues11to0; //Storing the mask value into R1 register
	
	//This code is storing the value in the port F register into the pointer register P0
	P0.L = lo(REG_PORTF_DATA);
	P0.H = hi(REG_PORTF_DATA);
	
	R2 = W[P0](Z); //Putting the value for the port F register into the R2 register (this is reading the values)
	R3 = MaskBitValues11to0; //Putting the mask value into the register R3
	
	returnValue_R0 = returnValue_R0 << 12; //Shifting the value for the LEDs up to the output pins
	
	R2 = R2 & R3; //Masking the port F register
	
	returnValue_R0 = returnValue_R0 | R2; //Oring the port F register with the correct value for the LED outputs
	
	[P0] = returnValue_R0; //Storing theses new output values into the port F register so it will display the correct LED orientation
	
	UNLINK;

_My_Write_GPIO_REB_OutputASM.END:
	RTS;
