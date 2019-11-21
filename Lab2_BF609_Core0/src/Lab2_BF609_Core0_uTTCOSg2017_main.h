/*************************************************************************************
* AUTO-GENERATED COMMENT - DO NOT MODIFY 
* Author: aidan
* Date: Thu 2019/10/24 at 02:31:12 PM
* File Type: uTTCOS Task Header File
*************************************************************************************/

#ifndef LAB2_BF609_CORE0_UTTCOSG2017_H
#define LAB2_BF609_CORE0_UTTCOSG2017_H

#include "faultyLED1_Thread.h"
#include <uTTCOSg2017/uTTCOSg.h>
#include <GPIO2017/ADSP_GPIO_interface.h>
#include <stdio.h>

#include "../../ENCM511_SpecificFiles/ENCM511_src/Example_faultyLED1_Thread.h"
#include "../../ENCM511_SpecificFiles/ENCM511_src/Example_uTTCOSg2017_main.h"
#include "../../ENCM511_SpecificFiles/ENCM511_include/FrontPanel_LED_Switches.h"

// extern "C" void BlackfinBF533_uTTCOSg_Audio_Rx_Tx_Task(void); 
extern "C" void SHARC21469_uTTCOSg_Audio_Rx_Tx_Task(void);
extern "C" void ADSP_SC589_uTTCOSg_Audio_Rx_Tx_Task(void);

// TODO -- Once you have demonstrated the idea of uTTCOS working with print statements
// Comment out the following include statement
// DON'T USE PRINT STATEMENT INSIDE uTTCOS as it is a real time system and
// print statements run on the HIGH priority emulator interrupt and disrupt real time operations
#include "faultyLED1_Thread.h"
#include "Front_Panel_Threads.h"
#include "REB_Threads.h"

extern "C" void ReadCycles_ASM(void);

void Custom_uTTCOS_OS_Init(unsigned long int);
extern "C" void Idle_WaitForInterrupts_ASM(void);
void uTTCOSg_Start_CoreTimer_Scheduler(unsigned int maxNumberThreads);


//Function Prototypes
void My_Init_SwitchInterface(void);
void My_Init_LEDInterface(void);
void My_Init_GPIO_REB_Input(void);
void My_Init_GPIO_REB_Output(void);

//extern "C" means that you are declaring these functions and they can be used in a different file as the compiler knows they are in an external file
//Pretty much they act in this case as global functions and are declared below

extern "C" unsigned long long int ReadProcessorCyclesASM(void);
extern "C" void My_Write_GPIO_REB_OutputASM(unsigned short int);
extern "C" unsigned short int My_Read_GPIO_REB_InputASM(void);
extern "C" void My_Init_GPIO_REB_InputASM(void);
extern "C" void My_Init_GPIO_REB_OutputASM(void);

//These variables are all declared and initialized to be false to begin until the respective function is called
//to initialize the respective equipment
extern bool My_Init_SwitchInterface_Done;
extern bool My_Init_LEDInterface_Done;
extern bool My_Init_GPIO_REB_Input_Done;
extern bool My_Init_GPIO_REB_Output_Done;
extern bool My_Init_GPIO_REB_Done;


#endif
