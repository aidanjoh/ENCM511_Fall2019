/*************************************************************************************
* AUTO-GENERATED COMMENT - DO NOT MODIFY 
* Author: smithmr 
* Date: Mon 2019/10/14 at 08:19:07 AM 
* File Type: TTCOS Main Header File
*************************************************************************************/

#ifndef FAULTYLEDTHREAD_H
#define FAULTYLEDTHREAD_H

#include "Example_faultyLED1_Thread.h"
#include "Example_faultyLED1_Thread.h"

#include <uTTCOSg2017/uTTCOSg.h>
#include <GPIO2017/ADSP_GPIO_interface.h>

#include <stdio.h>


// ***********  Exam question  hint
// ***********  I have included this .h file inside itself ***
// Thats an "infinite" include loop which should never stop preprocessing
// What special feature inside this .h file stops the infinite loop?
// Explain why that feature works!

void Task_RemoveMeSoon_Print1(void);
void Task_RemoveMeSoon_Print2(void);
void Set_Up_NOT_START_RemoveMeSoonTasks(void);
void KillerOfPrintStatements_Hunting(void);
void KillerOfPrintStatements(void);
void TheEnd(void);

extern "C" unsigned long long int ReadProcessorCyclesASM(void);
#endif
