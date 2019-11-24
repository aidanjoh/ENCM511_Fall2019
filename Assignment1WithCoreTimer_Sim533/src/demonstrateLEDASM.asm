/*
 * demonstrateLEDASM.asm
 *
 *  Created on: Oct 30, 2019
 *      Author: aidan
 */
#include <blackfin.h>

#define MASK_LED 0xf000(Z)
#define INCOMING_PAR R0
#define LED1BIT 0x1000(Z)
#define LED2BIT 0x2000(Z)
#define LED3BIT 0x4000(Z)
#define LED4BIT 0x8000(Z)
#define MASK_BITS11TO0 0x0fff(Z)

 	.section L1_data;
	
	.section program;
 	.global _demonstrateLEDASM;
 	
_demonstrateLEDASM:
 	LINK 20;
 	P0 = INCOMING_PAR;
 	nop;
 	nop;
 	nop;
 	nop;
	R1 = W[P0](Z);
	
	R0 = MASK_LED;
	R1 = R1 & R0;
	R1 = R1 >> 12;
	
	CC = R1 == 0;
	IF CC JUMP LED1;
	
	CC = R1 == 1;
	IF CC Jump LED2;
	
	CC = R1 == 2;
	IF CC Jump LED3;
	
	R3 = 4;
	
	CC = R1 == R3;
	IF CC Jump LED4;
	
	R3 = 8;
	
	CC = R1 == R3;
	IF CC Jump LED1;
	
LED1:
	R2 = LED1BIT;
	R1 = [P0];
	
	R3 = MASK_BITS11TO0;
	R1 = R1 & R3;
	
	R1 = R1 | R2;
	[P0] = R1;
	jump out;

LED2:
	R2 = LED2BIT;
	R1 = [P0];
	
	R3 = MASK_BITS11TO0;
	R1 = R1 & R3;
	
	R1 = R1 | R2;
	[P0] = R1;
	jump out;

LED3:
	R2 = LED3BIT;
	R1 = [P0];
	
	R3 = MASK_BITS11TO0;
	R1 = R1 & R3;
	
	R1 = R1 | R2;
	[P0] = R1;
	jump out;

LED4:
	R2 = LED4BIT;
	R1 = [P0];
	
	R3 = MASK_BITS11TO0;
	R1 = R1 & R3;
	
	R1 = R1 | R2;
	[P0] = R1;
	jump out;
out:

	UNLINK;
 _demonstrateLEDASM.end:
 RTS;