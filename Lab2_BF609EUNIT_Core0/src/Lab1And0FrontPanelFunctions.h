/*
 * Lab1And0FrontPanelFunctions.h
 *
 *  Created on: Nov 21, 2019
 *      Author: aidan
 */

#ifndef LAB1AND0FRONTPANELFUNCTIONS_H_
#define LAB1AND0FRONTPANELFUNCTIONS_H_

#include "Lab2EUNITTesting.h"

#define GARBAGEVALUE static_cast<unsigned char>(-1)

//Function Prototypes used in Lab 1 for FrontPanel
void myWriteFrontPanelLEDs(unsigned char);
unsigned char myReadFrontPanelSwitches(void);
unsigned char myReadFrontPanelLEDs(void);




#endif /* LAB1AND0FRONTPANELFUNCTIONS_H_ */
