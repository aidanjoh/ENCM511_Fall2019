/*************************************************************************************
* AUTO-GENERATED COMMENT - DO NOT MODIFY 
* Author: aidan 
* Date: Thu 2019/10/24 at 02:31:12 PM 
* File Type: TTCOS Faulty Flash code File
*************************************************************************************/

// This is an example of uTTCOS threads.


#include <uTTCOSg2017/uTTCOSg.h>
#include <GPIO2017/ADSP_GPIO_interface.h>

#include "faultyLED1_Thread.h"   // Should include links to other project header files

#include <stdio.h>

// TODO Adjust this parameter to match processor speed using emulator or simulator
#if defined(__ADSPBF609__)

#elif defined(__ADSPBF533__)

#else
	#error "Unknown processor"
#endif

extern "C" unsigned long int ReadCycles_ASM(void);

volatile char ID_Task_RemoveMeSoon_Print1 = 0;
void Task_RemoveMeSoon_Print1(void) {
	static unsigned int LEDState = 0;
	unsigned int newLEDState = LEDState;

	switch(LEDState) {
	case 0:
		printf("In Task_RemoveMeSoon_Print1 LED OFF at time 0x%8X system cycles\n", ReadCycles_ASM());
		newLEDState = 1;
		break;

	case 1:
		printf("In Task_RemoveMeSoon_Print1 LED  ON at time 0x%8X system cycles\n\n", ReadCycles_ASM());
		newLEDState = 0;
		break;
	}
	LEDState = newLEDState;
}


volatile char ID_Task_RemoveMeSoon_Print2 = 0;
void Task_RemoveMeSoon_Print2(void) {	
	static unsigned int LEDState = 0;
	unsigned int newLEDState = LEDState;

	switch(LEDState) {
	case 0:
		printf("In Task_RemoveMeSoon_Print2 LED OFF at time 0x%8X system cycles\n", ReadCycles_ASM());
		newLEDState = 1;
		break;

	case 1:
		printf("In Task_RemoveMeSoon_Print2 LED  ON at time 0x%8X system cycles\n", ReadCycles_ASM());
		newLEDState = 0;
		break;
	}
	LEDState = newLEDState;
}

 