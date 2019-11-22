/*
 * Front_Panel_Threads.cpp
 *
 *  Created on: Nov 19, 2019
 *      Author: aidan
 */

#include "Front_Panel_Threads.h"
#include "Lab1And0FrontPanelFunctions.h"

//Global Variables
static unsigned int pauseFrontPanelThreadFour = 0;
static unsigned long long int displayRate = DISPLAYRATEVALUE;
static unsigned long long int newDisplayRate= DISPLAYRATEVALUE;

void frontPanelThread1(void)
{
	static unsigned int LEDState = 0;
	FRONTPANEL_LED_8BIT_VALUE lastLEDStateValue;
	unsigned int nextLEDState = LEDState;

	switch(LEDState)
	{
		case 0: //This case is where the LED is off
			lastLEDStateValue = (myReadFrontPanelLEDs() & LED8MASK); //Zeroing the 8th LED bit
			myWriteFrontPanelLEDs(lastLEDStateValue);
			#if DEBUG
				printf("In Task_frontPanelThread1 LED OFF at time 0x%8X system cycles\n", ReadProcessorCyclesASM());
			#endif
			nextLEDState = 1;
			break;

		case 1: //This case is where the LED is on
			lastLEDStateValue = (myReadFrontPanelLEDs() & LED8MASK); //Zeroing the 8th LED bit
			lastLEDStateValue = lastLEDStateValue | LED8VALUE; //Placing a one into the 8th LED bit
			myWriteFrontPanelLEDs(lastLEDStateValue);
			#if DEBUG
				printf("In Task_frontPanelThread1 LED ON at time 0x%8X system cycles\n", ReadProcessorCyclesASM());
			#endif
			nextLEDState = 0;
			break;
	}

	LEDState = nextLEDState; //placing the nextLEDState into the LEDState variable
}

void frontPanelThread2(void)
{
	static unsigned int LEDState = 0;
	FRONTPANEL_LED_8BIT_VALUE lastLEDStateValue;
	unsigned int nextLEDState;

	switch(LEDState)
	{
		case 0: //This case is where the LED is off
			lastLEDStateValue = (myReadFrontPanelLEDs() & LED7MASK); //Zeroing the 7th LED bit
			myWriteFrontPanelLEDs(lastLEDStateValue);
			#if DEBUG
				printf("In Task_frontPanelThread2 LED OFF at time 0x%8X system cycles\n", ReadProcessorCyclesASM());
			#endif
			nextLEDState = 1;
			break;

		case 1: //This case is where the LED is on
			lastLEDStateValue = (myReadFrontPanelLEDs() & LED7MASK);
			lastLEDStateValue = (lastLEDStateValue | LED7VALUE); //Placing a one into the 7th LED bit
			myWriteFrontPanelLEDs(lastLEDStateValue);
			#if DEBUG
				printf("In Task_frontPanelThread2 LED ON at time 0x%8X system cycles\n", ReadProcessorCyclesASM());
			#endif
			nextLEDState = 2;
			break;

		case 2: //This is another case where the LED is on
			lastLEDStateValue = (myReadFrontPanelLEDs() & LED7MASK);
			lastLEDStateValue = (lastLEDStateValue | LED7VALUE); //Placing a one into the 7th LED bit
			myWriteFrontPanelLEDs(lastLEDStateValue);
			#if DEBUG
				printf("In Task_frontPanelThread2 LED ON at time 0x%8X system cycles\n", ReadProcessorCyclesASM());
			#endif
			nextLEDState = 0;
			break;
	}

	LEDState = nextLEDState; //Placing the nextLEDState into the LEDState variable
}

void frontPanelThread3(void)
{
	static unsigned int LEDState = 0;
	FRONTPANEL_LED_8BIT_VALUE lastLEDStateValue;
	unsigned int nextLEDState = LEDState;

	switch(LEDState)
	{
		case 0: //This case is where LED 1 and LED 2 are off representing 0
			lastLEDStateValue = (myReadFrontPanelLEDs() & LED1TO2MASK);
			myWriteFrontPanelLEDs(lastLEDStateValue); //This will be displaying the value 0
			#if DEBUG
				printf("In Task_frontPanelThread3 the LED Value is %d at time 0x%8X system cycles\n", lastLEDStateValue, ReadProcessorCyclesASM());
			#endif
			nextLEDState = 1;
			break;

		case 1: //This case is where LED 1 is on and LED 2 is off representing 1
			lastLEDStateValue = (myReadFrontPanelLEDs() & LED1TO2MASK);
			lastLEDStateValue = (lastLEDStateValue | LED1VALUE); //This will be displaying the value 1
			myWriteFrontPanelLEDs(lastLEDStateValue);
			#if DEBUG
				printf("In Task_frontPanelThread3 the LED Value is %d at time 0x%8X system cycles\n", lastLEDStateValue, ReadProcessorCyclesASM());
			#endif
			nextLEDState = 2;
			break;

		case 2: //This case is where LED 1 is off and LED 2 is on representing 2
			lastLEDStateValue = (myReadFrontPanelLEDs() & LED1TO2MASK);
			lastLEDStateValue = (lastLEDStateValue | LED2VALUE); //This will be displaying the value 2
			myWriteFrontPanelLEDs(lastLEDStateValue);
			#if DEBUG
				printf("In Task_frontPanelThread3 the LED Value is %d at time 0x%8X system cycles\n", lastLEDStateValue, ReadProcessorCyclesASM());
			#endif
			nextLEDState = 3;
			break;

		case 3: //This case is where LED 1 is on and LED 2 is on representing 3
			lastLEDStateValue = (myReadFrontPanelLEDs() & LED1TO2MASK);
			lastLEDStateValue = (lastLEDStateValue | LED1TO2VALUE); //This will be displaying the value 3
			myWriteFrontPanelLEDs(lastLEDStateValue);
			#if DEBUG
				printf("In Task_frontPanelThread3 the LED Value is %d at time 0x%8X system cycles\n", lastLEDStateValue, ReadProcessorCyclesASM());
			#endif
			nextLEDState = 0;
			break;
	}

	LEDState = nextLEDState; // Placing nextLEDState into the LEDState variable
}

void frontPanelThread4(void)
{
	static const FRONTPANEL_LED_8BIT_VALUE initials[] = {0x00, 0xe0, 0x1c, 0x13, 0x1c, 0xe0, 0x00, 0xc0, 0x00, 0xe0, 0xc3, 0xff, 0x03, 0x00, 0xc0}; //Aidan's initials array from Lab 0
	static unsigned int index = 0;

	FRONTPANEL_LED_8BIT_VALUE lastLEDValue;
	FRONTPANEL_LED_8BIT_VALUE newLEDValue;

	unsigned int nextState;

	if(pauseFrontPanelThreadFour == 0) //This code will be run if thread four is not paused
	{
		lastLEDValue = (myReadFrontPanelLEDs() & LED3TO6MASK);
		newLEDValue = initials[index] & LED3TO6VALUE; //newLEDValue will have the value in the initials array at the index, index for only the 3rd bit to the 6th bit
		newLEDValue = newLEDValue | lastLEDValue; //Putting the lastLEDValue with the value from the array to make sure that no bits were overwritten
		myWriteFrontPanelLEDs(newLEDValue);
		if (displayRate == 0) //if displayRate is equal to zero display the next value
		{
			displayRate = DISPLAYRATEVALUE;
			index++; //Incrementing the index
			#if DEBUG
				printf("In Task_frontPanelThread4 the LED Value is %d at time 0x%8X system cycles\n", newLEDValue, ReadProcessorCyclesASM());
			#endif
			if(initials[index] == INITIALSARRAYLENGTH) //Making sure we reset the initials array when the index gets to its length
			{
				index = 0;
			}
		}
		displayRate--; //Decrementing the displayRate
	}

}

void frontPanelThread5(void)
{
	static unsigned int switchState = 0;
	FRONTPANEL_LED_8BIT_VALUE lastLEDStateValue;
	unsigned int nextSwitchState;
	unsigned int switchOneValue;
	static unsigned long long int timeSwitchIsPressedFor = 0;
	static unsigned long long int timeThatThePressOccured;
	static unsigned long long int currentTime;

	switch(switchState)
	{
		case 0: //This case is where it is checking if SW on the Front Panel has been pressed and if it has it records the time that it is pressed at
			switchOneValue = (myReadFrontPanelSwitches()) & FRONTPANELSWITCHONEVALUE;
			if(switchOneValue == 1)
			{
				timeThatThePressOccured = ReadProcessorCyclesASM();
				#if DEBUG
					printf("In Task_frontPanelThread5 the switch State is %d at time 0x%8X system cycles\n", switchState, ReadProcessorCyclesASM());
				#endif
				nextSwitchState = 1;
			}
			else
			{
				nextSwitchState = 0;
			}
			break;

		case 1: //This case is where it is checking if SW1 is still pressed or if it has been released
			switchOneValue = (myReadFrontPanelSwitches()) & FRONTPANELSWITCHONEVALUE;
			if (switchOneValue == 1)
			{
				nextSwitchState = 1;
			}
			else //If SW1 has been relased it records the time and then calculates the time that the SW was pressed for
			{
				currentTime = ReadProcessorCyclesASM();

				#if DEBUG
					printf("In Task_frontPanelThread5 the switch State is %d at time 0x%8X system cycles\n", switchState, ReadProcessorCyclesASM());
				#endif

				timeSwitchIsPressedFor = currentTime - timeThatThePressOccured;

				#if DEBUG
					printf("%llu \n", timeSwitchIsPressedFor);
					printf("%f \n", (timeSwitchIsPressedFor/(double)(ONESECOND)));
				#endif

				if ((timeSwitchIsPressedFor >= ONESECOND) && (timeSwitchIsPressedFor <= TWOSECONDS)) //If the time that SW1 was pressed is between 1-2seconds it will speed up the FP LEDS 3-6
				{
					pauseFrontPanelThreadFour = 0;
					nextSwitchState = 2;

					#if DEBUG
					printf("You have speed up the Front Panel LEDS \n");
					#endif
				}
				else if((timeSwitchIsPressedFor >= THREESECONDS) && (timeSwitchIsPressedFor <= FOURSECONDS)) //If the time that SW1 was pressed is between 3-4 seconds it will slow down the FP LEDS 3-6
				{
					pauseFrontPanelThreadFour = 0;
					nextSwitchState = 3;

					#if DEBUG
						printf("You have slowed down the Front Panel LEDS \n");
					#endif
				}
				else
				{
					pauseFrontPanelThreadFour = 1; //Giving the pauseFrontPanelThreadFour variable a one will pause the FP LEDS 3-6
					nextSwitchState = 0;

					#if DEBUG
					printf("You have paused the Front Panel LEDs \n");
					#endif
				}
			}
			break;

		case 2: //This case is where the DisplayRate gets incremented, which speeds up the time the initials array pattern is displayed by the LEDs
			newDisplayRate = newDisplayRate / INCREMENTORDECREMENTVALUE;
			if (newDisplayRate == 0)
			{
				newDisplayRate = 1; //This is making sure that the newDisplayRate doesn't ever stop the LEDs
			}

			nextSwitchState = 0;

			#if DEBUG
				printf("In Task_frontPanelThread5 the switch State is %d at time 0x%8X system cycles\n", switchState, ReadProcessorCyclesASM());
			#endif
			break;

		case 3: //This case is where the DisplayRate gets decremented, which slows down the time the initials array pattern is displayed by the LEDs
			newDisplayRate = newDisplayRate * INCREMENTORDECREMENTVALUE;
			nextSwitchState = 0;
			#if DEBUG
				printf("In Task_frontPanelThread5 the switch State is %d at time 0x%8X system cycles\n", switchState, ReadProcessorCyclesASM());
			#endif
			break;
	}

	switchState = nextSwitchState;
}

