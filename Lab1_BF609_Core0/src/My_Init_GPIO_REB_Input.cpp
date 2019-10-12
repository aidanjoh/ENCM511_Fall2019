/*
 * My_Init_GPIO_REB.cpp
 *
 *  Created on: Oct 10, 2019
 *      Author: aidan
 */
#include <blackfin.h>
#include "Lab1_BF609_Core0.h"

void My_Init_GPIO_REB_InputCpp(void)
{
	#ifdef __ADSPBF609__


		*pREG_PORTF_DATA = 0x0000; //Setting the portf data register to all 0's to begin with

		*pREG_PORTF_INEN = *pREG_PORTF_INEN & MaskBits15to12And7to0; //This is making sure we keep whatever values are in the other bits

		*pREG_PORTF_INEN = 0x0f00 | *pREG_PORTF_INEN;  //Making the enable point to the input pins 11-8

		*pREG_PORTF_POL = 0x0000; //Setting the portf polariy register to all 0's to begin with

	#endif
}
