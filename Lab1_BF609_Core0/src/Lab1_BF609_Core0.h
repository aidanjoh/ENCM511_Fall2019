/*****************************************************************************
 * Lab1_BF609_Core0.h
 *****************************************************************************/

#ifndef __LAB1_BF609_CORE0_H__
#define __LAB1_BF609_CORE0_H__

/* Add your custom header content here */

#include <stdio.h>
#include "../../ENCM511_SpecificFiles/ENCM511_include/FrontPanel_LED_Switches.h"
#include "../../ENCM511_SpecificFiles/ENCM511_include/ADSP_BF609_Utilities_Library.h"
#include "../../ENCM511_SpecificFiles/ENCM511_include/REB_GPIO_Input_Library.h"
#include "../../ENCM511_SpecificFiles/ENCM511_include/REB_GPIO_Output_Library.h"

#define GARBAGE_VALUE static_cast<unsigned char>(-1) //The garbage value is unsigned -1

//These variables are all declared and initialized to be false to begin until the respective function is called
//to initialize the respective equipment
static bool My_Init_SwitchInterface_Done = false;
static bool My_Init_LEDInterface_Done = false;
static bool My_Init_GPIO_REB_Input_Done = false;
static bool My_Init_GPIO_REB_Output_Done = false;

//Initialization Prototypes
void My_Init_LEDInterface(void);
void My_Init_SwitchInterface(void);
void My_Init_GPIO_REB_Input(void);
void My_Init_GPIO_REB_Output(void);

//Read Prototypes
unsigned char My_ReadSwitches(void);

//Write Prototypes
void My_WriteLED(unsigned char);
void My_Write_REB_LED(unsigned short int);

//Other Prototypes for Lab 1
void Start_Lab1(void);
void charToBinary(unsigned char, unsigned char*);
void WaitTillSwitch1PressedAndReleased(void);
void WaitTillSwitch2PressedAndReleased(void);
void WaitTillSwitch3PressedAndReleased(void);
extern "C" unsigned long long int ReadProcessorCyclesASM(void);


#endif /* __LAB1_BF609_CORE0_H__ */
