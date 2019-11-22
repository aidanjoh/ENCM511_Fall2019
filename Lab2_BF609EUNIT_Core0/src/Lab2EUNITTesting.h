/*************************************************************************************
* AUTO-GENERATED COMMENT - DO NOT MODIFY 
* Author: aidan
* Date: Thu 2019/11/21 at 10:55:00 AM
* File Type: EUNIT Test Header File
*************************************************************************************/

#ifndef LAB2EUNITTESTING_H
#define LAB2EUNITTESTING_H

#include "../../ENCM511_SpecificFiles/ENCM511_include/FrontPanel_LED_Switches.h"
#include "Front_Panel_Threads.h"
#include "Lab1And0FrontPanelFunctions.h"
#include "stdio.h"

//These variables are all declared and initialized to be false to begin until the respective function is called
//to initialize the respective equipment
extern bool My_Init_SwitchInterface_Done;
extern bool My_Init_LEDInterface_Done;
extern bool My_Init_GPIO_REB_Input_Done;
extern bool My_Init_GPIO_REB_Output_Done;
extern bool My_Init_GPIO_REB_Done;

//Extern Function Prototypes
extern "C" unsigned long long int ReadProcessorCyclesASM(void);
extern "C" void My_Write_GPIO_REB_OutputASM(unsigned short int);
extern "C" unsigned short int My_Read_GPIO_REB_InputASM(void);
extern "C" void My_Init_GPIO_REB_InputASM(void);
extern "C" void My_Init_GPIO_REB_OutputASM(void);

//Function Prototypes
void My_Init_SwitchInterface(void);
void My_Init_LEDInterface(void);
void My_Init_GPIO_REB_Input(void);
void My_Init_GPIO_REB_Output(void);

void UpdateEunitGui(void);	// Update EUNIT GUI with results from previous test

#endif
