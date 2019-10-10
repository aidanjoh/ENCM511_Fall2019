/*****************************************************************************
 * Lab0_BF609_MOCKEDLEDandSwitches_Core0.h
 *****************************************************************************/

#ifndef __LAB0_BF609_MOCKEDLEDANDSWITCHES_CORE0_H__
#define __LAB0_BF609_MOCKEDLEDANDSWITCHES_CORE0_H__

/* Add your custom header content here */


#include <stdio.h>
#include "../../ENCM511_SpecificFiles/ENCM511_include/FrontPanel_LED_Switches.h"
#include "../../ENCM511_SpecificFiles/ENCM511_include/ADSP_BF609_Utilities_Library.h"

//Prototypes

void Start_Lab0(void);
void My_Init_LEDInterface(void);
unsigned char My_ReadLED(void);
void My_Init_SwitchInterface(void);
unsigned char My_ReadSwitches(void);
void My_WriteLED(unsigned char);
void charToBinary(unsigned char, unsigned char*);
void WaitTillSwitch1PressedAndReleased(void);
void WaitTillSwitch2PressedAndReleased(void);
void WaitTillSwitch3PressedAndReleased(void);
extern "C" unsigned long long int ReadProcessorCyclesASM(void);

#endif /* __LAB0_BF609_MOCKEDLEDANDSWITCHES_CORE0_H__ */
