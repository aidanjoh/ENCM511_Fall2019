/*
 * Lab1And0FrontPanelFunctions.cpp
 *
 *  Created on: Nov 21, 2019
 *      Author: aidan
 */
#include "Lab1And0FrontPanelFunctions.h"

void myWriteFrontPanelLEDs(unsigned char neededLEDValue) //This function is writing the values to be displayed by the LEDs
{
	printf("%d \n", My_Init_LEDInterface_Done);
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
			return GARBAGEVALUE;
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
		return GARBAGEVALUE;
	}

	return Read_GPIO_FrontPanelLEDS();
}
