/*
 * Lab0_GeneralCode.cpp
 *
 *  Created on: September 19, 2019
 *      Author: Aidan
 */

#include <sys/platform.h>
#include "adi_initialize.h"
#include "Lab0_BF609_MOCKEDLEDandSwitches_Core0.h"
#include <stdio.h>

#define GARBAGE_VALUE 0xF2

//The garbage value was -1 before and (0xF2)

static bool My_Init_SwitchInterface_Done = false;

static bool My_Init_LEDInterface_Done = false;

static unsigned char lastLEDValueWritten = GARBAGE_VALUE;

//Underneath is a code stub
void Start_Lab0(void)
{
	printf("Here in Start_Lab0\n");


	//unsigned char switchValueBad = My_ReadSwitches();

	My_Init_SwitchInterface();

#if 1
	My_Init_LEDInterface();

	printf("Press Switch 1\n");

	WaitTillSwitch1PressedAndReleased();
	unsigned char intials[15] = {0x00, 0xe0, 0x1c, 0x13, 0x1c, 0xe0, 0x00, 0xc0, 0x00, 0xe0, 0xc3, 0xff, 0x03, 0x00, 0xc0};
	int count = 0;
	unsigned char switchValue = 0;

	unsigned long long int intialTime;
	unsigned long long int WaitTime = 480000000;
	unsigned long long int time;


	while(1)
	{
		intialTime = ReadProcessorCyclesASM();
		My_WriteLED(intials[count]); //printing intials line by line
		count = count + 1; //incrementing the counter

		switchValue = My_ReadSwitches();

		if(switchValue == 1)
		{
			//WaitTillSwitch1PressedAndReleased();
			WaitTime = WaitTime / 2; //decreasing the time to wait
			if(WaitTime == 0)
			{
				WaitTime = 480000000;
			}
		}
		else if(switchValue == 2)
		{
			//WaitTillSwitch2PressedAndReleased();
			WaitTime = WaitTime * 2; //increasing the time to wait
		}

		time = ReadProcessorCyclesASM();
		while(time < intialTime + WaitTime)
		{
			time = ReadProcessorCyclesASM();
		}

		//This is making sure the count does not go past the amount of indexes in my intials array
		if(count == 16)
		{
			count = 0;
		}
	}


/*
	unsigned char switchValue = My_ReadSwitches();

	if (switchValue != 3)
	{
		printf("Bad switch read test -- value was 0x%x \n", switchValue);
	}
*/

#endif

// This code I commented out below was for testing the functions at first
/*
	unsigned char useLEDValue = 0x42;

	My_WriteLED(useLEDValue);

	unsigned char checkLEDValue = My_ReadLED();

	if (checkLEDValue != useLEDValue)
	{
		printf("Bad LED read / write test\n");
	}
*/

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
#elseif
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

#ifdef __ADSPBF609__
	Init_GPIO_FrontPanelSwitches();
#endif
}

unsigned char My_ReadSwitches(void)
{
	printf("Stub for My_ReadSwitches()\n");
	if (My_Init_SwitchInterface_Done == false)
	{
		printf("Switch hardware not ready \n");
		return GARBAGE_VALUE;
	}

#ifdef __ADSPBF609__
	FRONTPANEL_SWITCH_5BIT_VALUE activeLowValues = Read_GPIO_FrontPanelSwitches();
	FRONTPANEL_SWITCH_5BIT_VALUE activeHighValues = ~activeLowValues;

#define MASK_KEEP_LOWER_FIVE_BITS 0x1F // use bit-wise
	FRONTPANEL_SWITCH_5BIT_VALUE wantedSwitchValueActiveHigh = activeHighValues & MASK_KEEP_LOWER_FIVE_BITS;
	return wantedSwitchValueActiveHigh;

#else
	return 0x55;
#endif

}

unsigned char My_ReadLED(void)
{
	printf("Stub for My_ReadLED()\n");
	return lastLEDValueWritten;
}

void My_WriteLED(unsigned char neededLEDValue)
{
	//printf("Stub for My_WriteLED() \n"); -> commented out to show clearly the intials

	if (My_Init_LEDInterface_Done == false)
	{
		printf("LED hardware not ready \n");
		return;
	}

#ifdef __ADSPBF609__
	//Char array holding the values to print out
	unsigned char binaryArray[9];
	charToBinary(neededLEDValue, binaryArray);
	Write_GPIO_FrontPanelLEDS(neededLEDValue);
	lastLEDValueWritten = neededLEDValue;

#else
	//Char array holding the values to print out
	unsigned char binaryArray[9];

	//Function converting the char to binary using the array holding the values
	charToBinary(neededLEDValue, binaryArray);
	printf("LED value - decimal %3d; hex 0x%2x; bit pattern %s \n", neededLEDValue, neededLEDValue, &binaryArray);
	lastLEDValueWritten = neededLEDValue;
#endif

}

void My_Init_LEDInterface(void)
{
	//printf("Stub for My_Init_LEDInterface() \n");
	My_Init_LEDInterface_Done = true;

#ifdef __ADSPBF609__
	Init_GPIO_FrontPanelLEDS();
#endif

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
			array[i] = ' '; // change to '0' to get binary, I have the space to properly print intials

		numberValueDuplicate = numberValueDuplicate >> 1;
	}
	array[8] = 0; //To end the string with a null character
}


void WaitTillSwitch1PressedAndReleased()
{
	FRONTPANEL_SWITCH_5BIT_VALUE switchValue = 0;
	while(1)
	{
		switchValue = My_ReadSwitches();
		if(switchValue == 1)
		{
			printf("SW 1 was pressed\n");
			while(1)
			{
				switchValue = My_ReadSwitches();
				if(switchValue != 1)
				{
					printf("SW 1 was released\n");
					return;
				}
			}
		}
	}
}

void WaitTillSwitch2PressedAndReleased()
{
	FRONTPANEL_SWITCH_5BIT_VALUE switchValue = 0;
	while(1)
	{
		switchValue = My_ReadSwitches();
		if(switchValue == 2)
		{
			printf("SW 2 was pressed");
			while(1)
			{
				switchValue = My_ReadSwitches();
				if(switchValue != 2)
				{
					printf("SW 2 was not released");
					return;
				}
			}
		}
	}
}

void WaitTillSwitch3PressedAndReleased()
{
	FRONTPANEL_SWITCH_5BIT_VALUE switchValue = 0;
	while(1)
	{
		switchValue = My_ReadSwitches();
		if(switchValue == 4)
		{
			printf("SW 3 was pressed");
			while(1)
			{
				switchValue = My_ReadSwitches();
				if(switchValue != 4)
				{
					printf("SW 3 was not released");
					return;
				}
			}
		}
	}
}
