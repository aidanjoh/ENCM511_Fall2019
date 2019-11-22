/*
 * REB_Threads.h
 *
 *  Created on: Nov 20, 2019
 *      Author: miche
 */

#ifndef REB_THREADS_H_
#define REB_THREADS_H_

#include "Lab2_BF609_Core0_uTTCOSg2017_main.h"
//All the REB ASM functions are in the main.h file

//Function Prototypes used in REB_Threads.cpp
void REBThread1(void);
void REBThread2(void);
void REBThread3(void);

//Variables used in the REB threads file
static bool Thread1_Control = true;
static unsigned short int hardWareArray [100];
static int array_index = 0;

//Switches
#define FP_SW5_ON 0x10
#define FP_SW_OFF 0x00
#define FP_SW4_ON 0x08
#define FP_SW3_ON 0x04
#define FP_SW2_ON 0x02
#define FP_SW1_ON 0x01


#endif /* REB_THREADS_H_ */
