/*
 * Front_Panel_Threads.h
 *
 *  Created on: Nov 19, 2019
 *      Author: aidan
 */

#ifndef FRONT_PANEL_THREADS_H_
#define FRONT_PANEL_THREADS_H_


#include "Lab2_BF609_Core0_uTTCOSg2017_main.h"

//Function Prototypes used in Front_Panel_Thread.cpp
void frontPanelThread1(void);
void frontPanelThread2(void);
void frontPanelThread3(void);
void frontPanelThread4(void);
void frontPanelThread5(void);

//Function Prototypes used in Lab 1 for FrontPanel
void myWriteFrontPanelLEDs(unsigned char);
unsigned char myReadFrontPanelSwitches(void);
unsigned char myReadFrontPanelLEDs(void);


#endif /* FRONT_PANEL_THREADS_H_ */
