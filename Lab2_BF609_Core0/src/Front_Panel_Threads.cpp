/*
 * Front_Panel_Threads.cpp
 *
 *  Created on: Nov 19, 2019
 *      Author: aidan
 */

#include "Front_Panel_Threads.h"

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

//Global Variables
static unsigned int pauseFrontPanelThreadFour = 0;


void frontPanelThread1(void)
{
	static unsigned int LEDState = 0;
	FRONTPANEL_LED_8BIT_VALUE lastLEDStateValue;
	unsigned int nextLEDState;

	switch(LEDState)
	{
		case 0:
			lastLEDStateValue = (myReadFrontPanelLEDS(void) & LED8MASK);
			My_WriteLED(lastLEDStateValue);
			nextLEDState = 1;
			break;

		case 1:
			lastLEDStateValue = (myReadFrontPanelLEDS(void) & LED8MASK);
			My_WriteLED(lastLEDStateValue);
			nextLEDState = 0;
			break;
	}

	LEDState = nextLEDState;
}

void frontPanelThread2(void)
{
	static unsigned int LEDState = 0;
	FRONTPANEL_LED_8BIT_VALUE lastLEDStateValue;
	unsigned int nextLEDState;

	switch(LEDState)
	{
		case 0:
			lastLEDStateValue = (myReadFrontPanelLEDS(void) & LED7MASK);
			My_WriteLED(lastLEDStateValue);
			nextLEDState = 1;
			break;

		case 1:
			lastLEDStateValue = (myReadFrontPanelLEDS(void) & LED7MASK);
			lastLEDStateValue = (lastLEDStateValue | LED7VALUE);
			My_WriteLED(lastLEDStateValue);
			nextLEDState = 2;
			break;

		case 2:
			lastLEDStateValue = (myReadFrontPanelLEDS(void) & LED7MASK);
			lastLEDStateValue = (lastLEDStateValue | LED7VALUE);
			My_WriteLED(lastLEDStateValue);
			nextLEDState = 0;
			break;
	}

	LEDState = nextLEDState;
}

void frontPanelThread3(void)
{
	static unsigned int LEDState = 0;
	FRONTPANEL_LED_8BIT_VALUE lastLEDStateValue;
	unsigned int nextLEDState;

	switch(LEDState)
	{
		case 0:
			lastLEDStateValue = (myReadFrontPanelLEDS(void) & LED1TO2MASK);
			My_WriteLED(lastLEDStateValue); //This will be displaying the value 0
			nextLEDState = 1;
			break;

		case 1:
			lastLEDStateValue = (myReadFrontPanelLEDS(void) & LED1TO2MASK);
			lastLEDStateValue = (lastLEDStateValue | LED1VALUE); //This will be displaying the value 1
			My_WriteLED(lastLEDStateValue);
			nextLEDState = 2;
			break;

		case 2:
			lastLEDStateValue = (myReadFrontPanelLEDS(void) & LED1TO2MASK);
			lastLEDStateValue = (lastLEDStateValue | LED2VALUE); //This will be displaying the value 2
			My_WriteLED(lastLEDStateValue);
			nextLEDState = 3;
			break;

		case 3:
			lastLEDStateValue = (myReadFrontPanelLEDS(void) & LED1TO2MASK);
			lastLEDStateValue = (lastLEDStateValue | LED1TO2VALUE); //This will be displaying the value 3
			My_WriteLED(lastLEDStateValue);
			nextLEDState = 0;
			break;
	}

	LEDState = nextLEDState;
}

void frontPanelThread4(void)
{
	//Might have to place in the global position
	static const FRONTPANEL_LED_8BIT_VALUE initials[15] = {0x00, 0xe0, 0x1c, 0x13, 0x1c, 0xe0, 0x00, 0xc0, 0x00, 0xe0, 0xc3, 0xff, 0x03, 0x00, 0xc0}; //My initials array from Lab 0
	static unsigned int index = 0;

	FRONTPANEL_LED_8BIT_VALUE lastLEDValue;
	FRONTPANEL_LED_8BIT_VALUE newLEDValue;

	unsigned int nextState;

	switch(pauseFrontPanelThreadFour)
	{
		lastLEDValue = (myReadFrontPanelLEDS(void) & LED3TO6VALUE);
		newLEDValue = initials[index] | LED3TO6MASK;
		My_WriteLED(lastLEDStateValue);


	}
}

void frontPanelThread5(void)
{

}
