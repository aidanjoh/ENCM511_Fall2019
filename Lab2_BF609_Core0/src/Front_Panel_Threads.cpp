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

#define FRONTPANELSWITCHONEVALUE 0x01
#define FRONTPANELSWITCHONEMASK (~FRONTPANELSWITCHONEVALUE)

#define DISPLAYRATEVALUE 100
#define INITIALSARRAYLENGTH 15
#define INCREMENTORDECREMENTVALUE 1.25

#define ONESECOND ((unsigned long int) 480000000)
#define TWOSECONDS (ONESECOND*2)
#define THREESECONDS (ONESECOND*3)
#define FOURSECONDS (ONESECOND*4)

#define MASK_KEEP_LOWER_FIVE_BITS 0x1F

#define DEBUG 1

//Global Variables
static unsigned int pauseFrontPanelThreadFour = 0;
static unsigned long long int displayRate = DISPLAYRATEVALUE; //100 is a random number I have chosen for now
static unsigned long long int newDisplayRate= DISPLAYRATEVALUE;

void frontPanelThread1(void)
{
	static unsigned int LEDState = 0;
	FRONTPANEL_LED_8BIT_VALUE lastLEDStateValue;
	unsigned int nextLEDState = LEDState;

	switch(LEDState)
	{
		case 0:
			lastLEDStateValue = (myReadFrontPanelLEDs() & LED8MASK);
			myWriteFrontPanelLEDs(lastLEDStateValue);
			#if DEBUG
				printf("In Task_frontPanelThread1 LED OFF at time 0x%8X system cycles\n", ReadProcessorCyclesASM());
			#endif
			nextLEDState = 1;
			break;

		case 1:
			lastLEDStateValue = (myReadFrontPanelLEDs() & LED8MASK);
			lastLEDStateValue = lastLEDStateValue | LED8VALUE;
			myWriteFrontPanelLEDs(lastLEDStateValue);
			#if DEBUG
			printf("In Task_frontPanelThread1 LED ON at time 0x%8X system cycles\n", ReadProcessorCyclesASM());
			#endif
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
			lastLEDStateValue = (myReadFrontPanelLEDs() & LED7MASK);
			myWriteFrontPanelLEDs(lastLEDStateValue);
			printf("In Task_frontPanelThread2 LED OFF at time 0x%8X system cycles\n", ReadProcessorCyclesASM());
			nextLEDState = 1;
			break;

		case 1:
			lastLEDStateValue = (myReadFrontPanelLEDs() & LED7MASK);
			lastLEDStateValue = (lastLEDStateValue | LED7VALUE);
			myWriteFrontPanelLEDs(lastLEDStateValue);
			printf("In Task_frontPanelThread2 LED ON at time 0x%8X system cycles\n", ReadProcessorCyclesASM());
			nextLEDState = 2;
			break;

		case 2:
			lastLEDStateValue = (myReadFrontPanelLEDs() & LED7MASK);
			lastLEDStateValue = (lastLEDStateValue | LED7VALUE);
			myWriteFrontPanelLEDs(lastLEDStateValue);
			printf("In Task_frontPanelThread2 LED ON at time 0x%8X system cycles\n", ReadProcessorCyclesASM());
			nextLEDState = 0;
			break;
	}

	LEDState = nextLEDState;
}

void frontPanelThread3(void)
{
	static unsigned int LEDState = 0;
	FRONTPANEL_LED_8BIT_VALUE lastLEDStateValue;
	unsigned int nextLEDState = LEDState;

	switch(LEDState)
	{
		case 0:
			lastLEDStateValue = (myReadFrontPanelLEDs() & LED1TO2MASK);
			myWriteFrontPanelLEDs(lastLEDStateValue); //This will be displaying the value 0
			printf("In Task_frontPanelThread3 the LED Value is %d at time 0x%8X system cycles\n", lastLEDStateValue, ReadProcessorCyclesASM());
			nextLEDState = 1;
			break;

		case 1:
			lastLEDStateValue = (myReadFrontPanelLEDs() & LED1TO2MASK);
			lastLEDStateValue = (lastLEDStateValue | LED1VALUE); //This will be displaying the value 1
			myWriteFrontPanelLEDs(lastLEDStateValue);
			printf("In Task_frontPanelThread3 the LED Value is %d at time 0x%8X system cycles\n", lastLEDStateValue, ReadProcessorCyclesASM());
			nextLEDState = 2;
			break;

		case 2:
			lastLEDStateValue = (myReadFrontPanelLEDs() & LED1TO2MASK);
			lastLEDStateValue = (lastLEDStateValue | LED2VALUE); //This will be displaying the value 2
			myWriteFrontPanelLEDs(lastLEDStateValue);
			printf("In Task_frontPanelThread3 the LED Value is %d at time 0x%8X system cycles\n", lastLEDStateValue, ReadProcessorCyclesASM());
			nextLEDState = 3;
			break;

		case 3:
			lastLEDStateValue = (myReadFrontPanelLEDs() & LED1TO2MASK);
			lastLEDStateValue = (lastLEDStateValue | LED1TO2VALUE); //This will be displaying the value 3
			myWriteFrontPanelLEDs(lastLEDStateValue);
			printf("In Task_frontPanelThread3 the LED Value is %d at time 0x%8X system cycles\n", lastLEDStateValue, ReadProcessorCyclesASM());
			nextLEDState = 0;
			break;
	}

	LEDState = nextLEDState;
}

void frontPanelThread4(void)
{
	//Might have to place in the global position
	static const FRONTPANEL_LED_8BIT_VALUE initials[] = {0x00, 0xe0, 0x1c, 0x13, 0x1c, 0xe0, 0x00, 0xc0, 0x00, 0xe0, 0xc3, 0xff, 0x03, 0x00, 0xc0}; //My initials array from Lab 0
	static unsigned int index = 0;

	FRONTPANEL_LED_8BIT_VALUE lastLEDValue;
	FRONTPANEL_LED_8BIT_VALUE newLEDValue;

	unsigned int nextState;

	switch(pauseFrontPanelThreadFour)
	{
		case 0:
			lastLEDValue = (myReadFrontPanelLEDs() & LED3TO6VALUE);
			newLEDValue = initials[index] | LED3TO6MASK;
			myWriteFrontPanelLEDs(lastLEDValue);
			if (displayRate == 0) //if displayRate is equal to zero display the next value
			{
				displayRate = DISPLAYRATEVALUE;
				index++;
				if(initials[index] == INITIALSARRAYLENGTH) //Making sure we reset the initials array
				{
					index = 0;
				}
			}
			else
			{
				displayRate--;
			}
			break;

		case 1:
			lastLEDValue = (myReadFrontPanelLEDs() & LED3TO6VALUE);
			myWriteFrontPanelLEDs(lastLEDValue);
			break;
	}
}

void frontPanelThread5(void)
{
	static unsigned int switchState = 0;
	FRONTPANEL_LED_8BIT_VALUE lastLEDStateValue;
	unsigned int nextSwitchState;
	unsigned int switchOneValue;
	static unsigned long long int timeSwitchIsPressedFor = 0;
	unsigned long long int timeThatThePressOccured;
	unsigned long long int currentTime;

	switch(switchState)
	{
		case 0:
			switchOneValue = (myReadFrontPanelSwitches()) & FRONTPANELSWITCHONEVALUE;
			if(switchOneValue == 1)
			{
				timeThatThePressOccured = ReadProcessorCyclesASM();
				nextSwitchState = 1;
			}
			else
			{
				nextSwitchState = 0;
			}
			break;

		case 1:
			switchOneValue = (myReadFrontPanelSwitches()) & FRONTPANELSWITCHONEVALUE;
			if (switchOneValue == 1)
			{
				nextSwitchState = 1;
			}
			else
			{
				currentTime = ReadProcessorCyclesASM();
				timeSwitchIsPressedFor = currentTime - timeThatThePressOccured;
				if ((timeSwitchIsPressedFor >= ONESECOND) && (timeSwitchIsPressedFor <= TWOSECONDS))
				{
					pauseFrontPanelThreadFour = 0;
					nextSwitchState = 2;

					#if DEBUG
					printf("You have slowed down the Front Panel LEDS /n");
					#endif
				}
				else if((timeSwitchIsPressedFor >= THREESECONDS) && (timeSwitchIsPressedFor <= FOURSECONDS))
				{
					pauseFrontPanelThreadFour = 0;
					nextSwitchState = 3;

					#if DEBUG
					printf("You have speed up the Front Panel LEDS /n");
					#endif
				}
				else
				{
					pauseFrontPanelThreadFour = 1;
					nextSwitchState = 0;

					#if DEBUG
					printf("You have paused the Front Panel LEDs /n");
					#endif
				}
			}
			break;

		//Could make case 2 and 3 into one case with another switch case
		case 2:
			newDisplayRate = newDisplayRate / INCREMENTORDECREMENTVALUE;
			if (newDisplayRate == 0)
			{
				newDisplayRate = 1; //This is making sure that the newDisplayRate doesn't ever stop the LEDs
			}

			nextSwitchState = 0;
			break;

		case 3:
			newDisplayRate = newDisplayRate * INCREMENTORDECREMENTVALUE;
			nextSwitchState = 0;
			break;
	}
}

void myWriteFrontPanelLEDs(unsigned char neededLEDValue) //This function is writing the values to be displayed by the LEDs
{
	if (My_Init_LEDInterface_Done == false)
	{
		return;
	}
	Write_GPIO_FrontPanelLEDS(neededLEDValue); //Writing the value to the panel of LEDs
}

unsigned char myReadFrontPanelSwitches(void) //This function is reading the switches from the panel
{
		if (My_Init_SwitchInterface_Done == false)
		{
			return -1;
		}

		FRONTPANEL_LED_8BIT_VALUE activeLowValues = Read_GPIO_FrontPanelSwitches();

		FRONTPANEL_LED_8BIT_VALUE activeHighValues = ~activeLowValues;

		FRONTPANEL_LED_8BIT_VALUE wantedSwitchValueActiveHigh = activeHighValues & MASK_KEEP_LOWER_FIVE_BITS;

		return wantedSwitchValueActiveHigh;
}

unsigned char myReadFrontPanelLEDs(void)
{
	if (My_Init_LEDInterface_Done == false)
	{
		return -1;
	}

	return Read_GPIO_FrontPanelLEDS();
}
