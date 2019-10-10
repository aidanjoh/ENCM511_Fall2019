/*
 * My_Write_GPIO_REB_Output.cpp
 *
 *  Created on: Oct 10, 2019
 *      Author: aidan
 */
#include <blackfin.h>

void My_Write_GPIO_REB_Output(unsigned short int LEDValueToDisplay)
{
	//*p means pointer
	//REG_PORTf_DATA is the input registers
	//We are writing LEDValueToDisplay but need to shift
	*pREG_PORTF_DATA = LEDValueToDisplay;

}
