/*
 * Lab1And0FrontPanelFunctions.h
 *
 *  Created on: Nov 21, 2019
 *      Author: aidan
 */

#ifndef LAB1AND0FRONTPANELFUNCTIONS_H_
#define LAB1AND0FRONTPANELFUNCTIONS_H_

#include "Assignment2CoffeePot_BF609_Core0.h"

#define GARBAGEVALUE static_cast<unsigned char>(-1)
#define MASK_KEEP_LOWER_FIVE_BITS 0x1F

//Function Prototypes used in Lab 1 for FrontPanel
void myWriteFrontPanelLEDs(unsigned char);
unsigned char myReadFrontPanelSwitches(void);
unsigned char myReadFrontPanelLEDs(void);




#endif /* LAB1AND0FRONTPANELFUNCTIONS_H_ */
