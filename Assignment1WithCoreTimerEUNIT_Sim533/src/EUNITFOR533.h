/*************************************************************************************
* AUTO-GENERATED COMMENT - DO NOT MODIFY 
* Author: aidan
* Date: Sun 2019/11/24 at 01:22:27 PM
* File Type: EUNIT Test Header File
*************************************************************************************/

#ifndef EUNITFOR533_H
#define EUNITFOR533_H

#include <blackfin.h>
void UpdateEunitGui(void);	// Update EUNIT GUI with results from previous test


//MACROS
#define CORETIMEPOWERBIT 0x00000001
#define CORETIMERAUTORLD 0x00000008

#define TCNTLBITS3AND1TO0 0x0000000b
#define TCNTLDONEBIT 0x00000008
#define NOTSTUBS 1
#define PERIOD 100000
#define COUNT 100000
#define TCNTLTMRENBIT 0x00000002
#define TCNTLTINTBIT 0x00000008
#define TCNTLTAUTORLDBIT 0x00000004
#define ARRAYLENGTH 10

//Prototypes for CoreTimer Functions for BF533
void myInit_CoreTimer(unsigned long int period, unsigned long int count);
void myControl_CoreTimer(unsigned short int cntrl_value);
bool myCompleted_CoreTimer(void);
void myTimedWaitOnCoreTimer(void);

extern "C" unsigned long long int ReadProcessorCyclesASM(void);

#endif
