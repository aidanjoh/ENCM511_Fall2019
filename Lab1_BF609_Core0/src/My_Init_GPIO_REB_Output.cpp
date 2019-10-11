/*
 * My_Init_GPIO_REB_Output.cpp
 *
 *  Created on: Oct 10, 2019
 *      Author: aidan
 */
#include <blackfin.h>
#include "Lab1_BF609_Core0.h"

void My_Init_GPIO_REB_OutputCpp(void)
{
	#ifdef __ADSPBF609__
		*pREG_PORTF_DIR = 0xf000 | *pREG_PORTF_DIR; //Making the direction point to the output pins 15-12
	#endif
}
