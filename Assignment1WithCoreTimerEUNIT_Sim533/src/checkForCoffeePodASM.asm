/*
 * checkForCoffeePodASM.asm
 *
 *  Created on: Oct 30, 2019
 *      Author: aidan
 */

#include <blackfin.h>

 	.section L1_data;
 	.section program;
 
 #define INCOMING_PAR R0
 #define TEMPERATURE 95
 #define COFFEEPOD 0x0800(Z)
 
 	.global _checkForCoffeePodASM;
 
_checkForCoffeePodASM:
	[--SP] = R4;
 	[--SP] = P4;
	LINK 16;
	
 	P4 = INCOMING_PAR;
	R4 = W[P4](Z);
	
	R0 = P4;
	
	.extern __Z22CurrentTemperature_CPPP16COFFEEPOT_DEVICE;
	CALL __Z22CurrentTemperature_CPPP16COFFEEPOT_DEVICE;
	
	R2 = R0;
	
	R3 = TEMPERATURE;
	CC = R3 <= R2;
	If CC jump second;
	
	jump Out;

second:
	R1 = COFFEEPOD;
	R2 = R4 & R1;
	CC = R2 == 0;
	If CC jump coffeePod;

coffeePod:
	R1 = COFFEEPOD;
	R0 = R4 | R1;
	[P4] = R0;
 
Out:
	UNLINK;
	[SP++] = P4;
	[SP++] = R4;
 _checkForCoffeePodASM.end:
 RTS;