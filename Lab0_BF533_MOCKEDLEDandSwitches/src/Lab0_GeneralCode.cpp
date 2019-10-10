/*
 * Lab0_GeneralCode.cpp
 *
 *  Created on: September 12, 2019
 *      Author: Aidan
 */

#include <sys/platform.h>
#include "adi_initialize.h"
#include "Lab0_BF533_MOCKEDLEDandSwitches.h"
#include <stdio.h>

#define GARBAGE_VALUE -1

static bool My_Init_SwitchInterface_Done = false;
static unsigned char lastLEDValueWritten = GARBAGE_VALUE;

//Underneath is a code stub
void Start_Lab0(void)
{
	printf("Here in Start_Lab0\n");


	unsigned char switchValueBad = My_ReadSwitches();

	My_Init_SwitchInterface();

#if 1
	My_Init_LEDInterface();

	printf("Press Switch 3\n");

	unsigned char switchValue = My_ReadSwitches();

	if (switchValue != 3)
	{
		printf("Bad switch read test\n");
	}
#endif


	unsigned char useLEDValue = 0x42;

	My_WriteLED(useLEDValue);

	unsigned char checkLEDValue = My_ReadLED();

	if (checkLEDValue != useLEDValue)
	{
		printf("Bad LED read / write test\n");
	}

#if 0
	for (useLEDValue = 0; useLEDValue <= 0x80; useLEDValue++)
	{
		My_WriteLED(useLEDValue);
		unsigned char checkLEDValue = My_ReadLED();
		if (checkLEDValue != useLEDValue)
		{
			printf("Bad LED read / write test -- wrote %d and got back %d \n", useLEDValue, checkLEDValue);
		}
		else
		{
			printf("wrote %d and got back %d \n", useLEDValue, checkLEDValue);
		}
	}
#else
	unsigned char intials[15] = {0x00, 0xe0, 0x1c, 0x13, 0x1c, 0xe0, 0x00, 0xc0, 0x00, 0xe0, 0xc3, 0xff, 0x03, 0x00, 0xc0};

	for(int count = 0; count < 15; count++)
	{
		My_WriteLED(intials[count]);
	}

#endif

	printf("leaving Start_Lab0\n");
}

void My_Init_SwitchInterface(void)
{
	printf("Stub for My_Init_SwitchInterface() \n");
	My_Init_SwitchInterface_Done = true;
}

unsigned char My_ReadSwitches(void)
{
	printf("Stub for My_ReadSwitches()\n");
	if (My_Init_SwitchInterface_Done == false)
	{
		printf("Switch hardware not ready \n");
		return GARBAGE_VALUE;
	}
}

unsigned char My_ReadLED(void)
{
	printf("Stub for My_ReadLED()\n");
	return lastLEDValueWritten;
}

void My_WriteLED(unsigned char neededLEDValue)
{
	//printf("Stub for My_WriteLED() \n"); -> commented out to show clearly the intials

	unsigned char binaryArray[9];
	charToBinary(neededLEDValue, binaryArray);
	printf("LED value - decimal %3d; hex 0x%2x; bit pattern %s \n", neededLEDValue, neededLEDValue, &binaryArray);
	lastLEDValueWritten = neededLEDValue;
}

void My_Init_LEDInterface(void)
{
	printf("Stub for My_Init_LEDInterface() \n");
}

void charToBinary(unsigned char charValue, unsigned char* array)
{
	unsigned char numberValueDuplicate = charValue;
	char i;
	for (i = 7; i >= 0; i--)
	{
		if (numberValueDuplicate & 0x01)
			array[i] = '1';
		else
			array[i] = ' '; //change to '0' to get binary
		numberValueDuplicate = numberValueDuplicate >> 1;
	}
	array[8] = 0;
}
