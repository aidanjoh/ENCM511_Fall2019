/*************************************************************************************
* AUTO-GENERATED COMMENT - DO NOT MODIFY 
* Author: aidan 
* Date: Tue 2019/12/03 at 04:44:37 PM 
* File Type: TTCOS Main Header File
*************************************************************************************/

#ifndef FAULTYLEDTHREAD_H
#define FAULTYLEDTHREAD_H

#include <uTTCOSg2017/uTTCOSg.h>
#include <GPIO2017/ADSP_GPIO_interface.h>

#include "faultyLED1_Thread.h"

#include <stdio.h>


// ***********  Exam question  hint
// ***********  I have included this .h file inside itself ***
// Thats an "infinite" include loop which should never stop preprocessing
// What special feature inside this .h file stops the infinite loop?
// Explain why that feature works!
#include "faultyLED1_Thread.h"

void Task_RemoveMeSoon_Print1(void);
void Task_RemoveMeSoon_Print2(void);
void Set_Up_NOT_START_RemoveMeSoonTasks(void);
void KillerOfPrintStatements_Hunting(void);
void KillerOfPrintStatements(void);
void TheEnd(void);

extern "C" unsigned long long int ReadProcessorCyclesASM(void);
#endif
