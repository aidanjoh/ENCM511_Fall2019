/*
 * My_Write_GPIO_REB_Output.cpp
 *
 *  Created on: Oct 10, 2019
 *      Author: aidan
 */
#include <blackfin.h>
#include "Lab1_BF609_Core0.h"

void My_Write_GPIO_REB_Output(unsigned short int LEDValueToDisplay)
{
	unsigned short int TempValue;
	LEDValueToDisplay = LEDValueToDisplay << 12; //Shifting the bits by 12 to output to the Port for the LEDS as they are pins 12-15
	TempValue = *pREG_PORTF_DATA & 0x0fff; //Creating a Temporary value to hold the masked values of the portf data
	*pREG_PORTF_DATA = LEDValueToDisplay | TempValue; //Placing the LED Value into the PORTF register
}
