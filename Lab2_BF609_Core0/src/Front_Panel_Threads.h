/*
 * Front_Panel_Threads.h
 *
 *  Created on: Nov 19, 2019
 *      Author: aidan
 */

#ifndef FRONT_PANEL_THREADS_H_
#define FRONT_PANEL_THREADS_H_


#include "Lab2_BF609_Core0_uTTCOSg2017_main.h"


//MACROS
#define LED8VALUE 0x80
#define LED8MASK (~LED8VALUE)

#define LED7VALUE 0x40
#define LED7MASK (~LED7VALUE)

#define LED6VALUE 0x20
#define LED6MASK (~LED6VALUE)

#define LED5VALUE 0x10
#define LED5MASK (~LED5VALUE)

#define LED4VALUE 0x08
#define LED4MASK (~LED4VALUE)

#define LED3VALUE 0x04
#define LED3MASK (~LED3VALUE)

#define LED2VALUE 0x02
#define LED2MASK (~LED2VALUE)

#define LED1VALUE 0x01
#define LED1MASK (~LED1VALUE)

#define LED3TO6VALUE 0x3c
#define LED3TO6MASK (~LED3TO6VALUE)

#define LED1TO2VALUE 0x03
#define LED1TO2MASK (~LED1TO2VALUE)

#define FRONTPANELSWITCHONEVALUE 0x01
#define FRONTPANELSWITCHONEMASK (~FRONTPANELSWITCHONEVALUE)

#define DISPLAYRATEVALUE 50
#define INITIALSARRAYLENGTH 15
#define INCREMENTORDECREMENTVALUE 1.25

#define ONESECOND ((unsigned long int) 480000000)
#define TWOSECONDS (ONESECOND*2)
#define THREESECONDS (ONESECOND*3)
#define FOURSECONDS (ONESECOND*4)

#define MASK_KEEP_LOWER_FIVE_BITS 0x1F

#define GARBAGEVALUE static_cast<unsigned char>(-1)
#define DEBUG 0

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
