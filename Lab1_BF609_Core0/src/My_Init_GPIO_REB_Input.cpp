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
		*pREG_PORTF_DATA = 0x0000;
		*pREG_PORTF_INEN = 0x0f00 | *pREG_PORTF_INEN;  //Making the enable point to the input pins 11-8
		*pREG_PORTF_POL = 0x0000;

	#endif
}
