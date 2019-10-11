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
	LEDValueToDisplay = LEDValueToDisplay << 12; //Shifting the bits by 12 to output to the Port for the LEDS as they are pins 12-15
	*pREG_PORTF_DATA = LEDValueToDisplay;
}
