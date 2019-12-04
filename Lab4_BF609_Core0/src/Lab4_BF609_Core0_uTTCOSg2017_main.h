/*************************************************************************************
* AUTO-GENERATED COMMENT - DO NOT MODIFY 
* Author: aidan
* Date: Tue 2019/12/03 at 04:44:37 PM
* File Type: uTTCOS Task Header File
*************************************************************************************/

#ifndef LAB4_BF609_CORE0_UTTCOSG2017_H
#define LAB4_BF609_CORE0_UTTCOSG2017_H

#include <uTTCOSg2017/uTTCOSg.h>
#include <GPIO2017/ADSP_GPIO_interface.h>
// extern "C" void BlackfinBF533_uTTCOSg_Audio_Rx_Tx_Task(void); 
extern "C" void SHARC21469_uTTCOSg_Audio_Rx_Tx_Task(void);
extern "C" void ADSP_SC589_uTTCOSg_Audio_Rx_Tx_Task(void);

// TODO -- Once you have demonstrated the idea of uTTCOS working with print statements
// Comment out the following include statement
// DON'T USE PRINT STATEMENT INSIDE uTTCOS as it is a real time system and
// print statements run on the HIGH priority emulator interrupt and disrupt real time operations
#include "faultyLED1_Thread.h"

#include <stdint.h>
#include "../../ENCM511_SpecificFiles/ENCM511_include/REB_SPI_Library.h"
#include "../../ENCM511_SpecificFiles/ENCM511_include/GP_Timer_Library.h"
#include "../../ENCM511_SpecificFiles/ENCM511_src/Example_uTTCOSg2017_main.h"
#include "../../ENCM511_SpecificFiles/ENCM511_src/Example_faultyLED1_Thread.h"
#include "../../ENCM511_SpecificFiles/ENCM511_include/ADSP_BF609_Utilities_Library.h"
#include <string.h>

void SetBoardLED_SPI_ConfigSoftSwitches(void);
int32_t Smith_adi_initpinmux(void);

#include <stdio.h>

void Custom_uTTCOS_OS_Init(unsigned long int);
extern "C" void Idle_WaitForInterrupts_ASM(void);
void uTTCOSg_Start_CoreTimer_Scheduler(unsigned int maxNumberThreads);

//Initilaizing Thread
void initializeLCD(void);
void waitABit(unsigned long int timeValue);
void writingTemperature(void);
void clearScreen(void);

//Three threads
void writingPrelabMessage(void);
void writingTemperatureMessage(void);
void writingInitials(void);

//Message Thread
void stringToLCDScreen(char* message, unsigned long TargetBuffer);


#endif
