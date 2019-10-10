/*
 * My_Read_GPIO_REB_Input.cpp
 *
 *  Created on: Oct 10, 2019
 *      Author: aidan
 */
#include <blackfin.h>
#include "Lab1_BF609_Core0.h"

unsigned short int My_Read_GPIO_REB_Input(void)
{
	unsigned short int switchREBValue; //Declaring a short int (16bits) switchREBValue
	switchREBValue = *pREG_PORTF_DATA; //This statement is storing the value from the pointer holding port F register data
	switchREBValue = switchREBValue & MASK_KEEP_BITS_11_TO_8; //This statement is just selecting the bits from PF8-11
	switchREBValue = switchREBValue >> 8; //Shift the bits down by 8 to get the correct correlated switch values
	return switchREBValue;
}
