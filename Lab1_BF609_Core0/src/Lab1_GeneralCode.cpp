/*
 * Lab1_GeneralCode.cpp
 *
 *  Created on: Oct 8, 2019
 *      Author: Aidan and Michele
 */

#include <sys/platform.h>
#include "adi_initialize.h"
#include "Lab1_BF609_Core0.h"

void Start_Lab1(void) //Code stub for Start Lab1
{
	printf("Here in Start_Lab1\n"); //This is declaring it is the start of Lab 1

	My_Init_SwitchInterface();  //This function is initiating the switches on the panel
	My_Init_GPIO_REB_Input(); //This function is initiating the switches on the board
	My_Init_LEDInterface();  //This function is initiating the LEDS on the panel
	My_Init_GPIO_REB_Output(); //This function is initiating the LEDs on the board

	printf("Please Press Switch 1 to Begin the Lab\n"); //Pressing Switch 1 will initiate the Start of the Lab

	WaitTillSwitchREB1PressedAndReleased(); //This function is in place to make sure that switch 1 was pressed and then released

	//The array below holds the hex values for Aidan's initials
	unsigned char initials[15] = {0x00, 0xe0, 0x1c, 0x13, 0x1c, 0xe0, 0x00, 0xc0, 0x00, 0xe0, 0xc3, 0xff, 0x03, 0x00, 0xc0};

	//The array below holds random short integer value to display the LED lights
	unsigned short int array[4] = {0x0000, 0x0001, 0x0002, 0x0003}; //Array to test the LEDs

	//The array below will be the array that will be filled by the hardware from switch pressing
	unsigned short int hardwareFilledArray[100];

	int count = 0; //Creating a counter value
	unsigned char switchValue = 0; //Creating a value to hold the switch Value
	unsigned short int switchREBValue = 0; //Creating a value to hold the switch REB Value

	//Switch 1 has a value of: 0x01
	//Switch 2 has a value of: 0x02
	//Switch 3 has a value of: 0x04
	//Switch 4 has a value of: 0x08

	unsigned long long int initialTime; //This variable will hold the initial Time
	unsigned long long int WaitTime = 480000000; //The wait time was selected to be 1 second which is equal to 480000000 processor cycles
	unsigned long long int time; //This variable will hold the time

	while(1)
	{
		//if(switchREBValue == 2 || switchREBValue == 3)
			//do lab 1 code
		//else if(switchREBValue == 1 || switchREBValue == 0)
			//do lab 0 code where the speed control will be done by the frontpanel switches and can be reset back to this choice by pressing SW5

		initialTime = ReadProcessorCyclesASM();
		//My_WriteLED(initials[count]); //printing initials line by line for the front Panel

		My_Write_REB_LED(array[count]);

		count = count + 1; //incrementing the counter

		//switchValue = My_ReadSwitches();

		switchREBValue = My_Read_REB_Switches();

		if(switchREBValue == 1)
		{
			//WaitTillSwitch1PressedAndReleased();
			WaitTime = WaitTime / 2; //decreasing the time to wait
			if(WaitTime == 1)
			{
				WaitTime = WaitTime * 2; //This is here to make sure the wait time does not get too fast
			}
		}
		else if(switchREBValue == 2)
		{
			//WaitTillSwitch2PressedAndReleased();
			WaitTime = WaitTime * 2; //increasing the time to wait
		}

		time = ReadProcessorCyclesASM();
		while(time < initialTime + WaitTime)
		{
			time = ReadProcessorCyclesASM();
		}

		//This is making sure the count does not go past the amount of indexes in my intials array
		if(count == 4) //was 16 for initials
		{
			count = 0;
		}
	}
}

unsigned char My_ReadSwitches(void) //This function is reading the switches from the panel
{
	printf("Stub for My_ReadSwitches()\n");

	#ifdef __ADSPBF609__
			if (My_Init_SwitchInterface_Done == false)
			{
				printf("Switch hardware not ready \n");
				return GARBAGE_VALUE;
			}

			FRONTPANEL_SWITCH_5BIT_VALUE activeLowValues = Read_GPIO_FrontPanelSwitches();
			FRONTPANEL_SWITCH_5BIT_VALUE activeHighValues = ~activeLowValues;


			#define MASK_KEEP_LOWER_FIVE_BITS 0x1F // use bit-wise
			FRONTPANEL_SWITCH_5BIT_VALUE wantedSwitchValueActiveHigh = activeHighValues & MASK_KEEP_LOWER_FIVE_BITS;
			return wantedSwitchValueActiveHigh;
	#else
		return 0x55;
	#endif

}

unsigned short int My_Read_REB_Switches(void)
{
		if(My_Init_GPIO_REB_Input_Done == false) //My_Init_GPIO_REB_Input_Done for his function
		{
			printf("Switch hardware not ready \n");
			return GARBAGE_VALUE1;
		}

		REB_BITS16 wantedSwitchOnBoardValueActiveHigh = My_Read_GPIO_REB_Input(); //The board is active high
		return wantedSwitchOnBoardValueActiveHigh;
}

void My_Write_REB_LED(unsigned short int LEDValue) //This function is writing the values for the REB LEDs
{
	//printf("Stub for My_Write_REB_LED() \n");

	if (My_Init_GPIO_REB_Output_Done == false) // My_Init_GPIO_REB_Output_Done for his function
	{
		printf("LED hardware not ready \n");
		return;
	}

	#ifdef __ADSPBF609__
		My_Write_GPIO_REB_OutputASM(LEDValue);
	#endif
}

void My_WriteLED(unsigned char neededLEDValue) //This function is writing the values to be displayed by the LEDs
{
	//printf("Stub for My_WriteLED() \n");

	if (My_Init_LEDInterface_Done == false)
	{
		printf("LED hardware not ready \n");
		return;
	}

#ifdef __ADSPBF609__
	Write_GPIO_FrontPanelLEDS(neededLEDValue); //Writing the value to the panel of LEDs

#else //This is for the 533 emulator
	//Char array holding the values to print out
	unsigned char binaryArray[9];
	charToBinary(neededLEDValue, binaryArray); //Function converting the char to binary using the array holding the values
	printf("LED value - decimal %3d; hex 0x%2x; bit pattern %s \n", neededLEDValue, neededLEDValue, &binaryArray);
#endif

}

void My_Init_SwitchInterface(void) //This function is initializing the Switches on the Panel
{
	//printf("Stub for My_Init_SwitchInterface() \n");
	My_Init_SwitchInterface_Done = true;

#ifdef __ADSPBF609__
	Init_GPIO_FrontPanelSwitches();
#endif
}

void My_Init_LEDInterface(void) //This function is initializing the LEDs on the Panel
{
	//printf("Stub for My_Init_LEDInterface() \n");
	My_Init_LEDInterface_Done = true;

	#ifdef __ADSPBF609__
		Init_GPIO_FrontPanelLEDS();
	#endif

}

void My_Init_GPIO_REB_Input(void) //This function is initializing the switches on the Board
{
	//printf("Stub for My_Init_GPIO_REB_Input() \n");
	My_Init_GPIO_REB_Input_Done = true;

	#ifdef __ADSPBF609__
#if 0
		My_Init_GPIO_REB_InputCpp();
#else
		My_Init_GPIO_REB_InputASM();
#endif

	#endif
}

void My_Init_GPIO_REB_Output(void) //This function is initializing the LEDs on the Board
{
	//printf("Stub for My_Init_GPIO_REB_Output");
	My_Init_GPIO_REB_Output_Done = true;

	#ifdef __ADSPBF609__
#if 0
		My_Init_GPIO_REB_OutputCpp();
#else
		My_Init_GPIO_REB_OutputASM();
#endif
	#endif
}

void charToBinary(unsigned char charValue, unsigned char* array) //This is my function to convert the char value into a binary number for the operation to display my initials
{
	unsigned char numberValueDuplicate = charValue;
	char i;
	for (i = 7; i >= 0; i--)
	{
		if (numberValueDuplicate & 0x01)
			array[i] = '1';
		else
			array[i] = ' '; // change to '0' to get binary, I have the space to properly print initials

		numberValueDuplicate = numberValueDuplicate >> 1; //Shifting the bits by 1
	}
	array[8] = 0; //To end the string with a null character
}

void WaitTillSwitchREB1PressedAndReleased() //This function is making sure that Switch REB 1 is pressed and released
{
	unsigned short int switchValue = 0;
	while(1)
	{
		switchValue = My_Read_REB_Switches();
		if(switchValue == 0x1)
		{
			while(1)
			{
				switchValue = My_Read_REB_Switches();
				unsigned char bitValue = switchValue & 0x1;
				if(bitValue == 0x0)
				{
					break;
				}
			}
			break;
		}
	}
}

void WaitTillSwitchREB2PressedAndReleased() //This function is making sure that Switch REB 2 is pressed and released
{
	unsigned short int switchValue = 0;
	while(1)
	{
		switchValue = My_Read_REB_Switches();
		if(switchValue == 0x2)
		{
			while(1)
			{
				switchValue = My_Read_REB_Switches();
				unsigned char bitValue = switchValue & 0x2;
				if(bitValue == 0x0)
				{
					break;
				}
			}
			break;
		}
	}
}

void WaitTillSwitchREB3PressedAndReleased() //This function is making sure that Switch REB 3 is pressed and released
{
	unsigned short int switchValue = 0;
	while(1)
	{
		switchValue = My_Read_REB_Switches();
		if(switchValue == 0x4)
		{
			while(1)
			{
				switchValue = My_Read_REB_Switches();
				unsigned char bitValue = switchValue & 0x4;
				if(bitValue == 0x0)
				{
					break;
				}
			}
			break;
		}
	}
}

void WaitTillSwitch1PressedAndReleased() //This function is making sure that Switch 1 is pressed and released
{
	unsigned char switchValue = 0;
	while(1)
	{
		switchValue = My_ReadSwitches();
		if(switchValue == 0x1)
		{
			while(1)
			{
				switchValue = My_ReadSwitches();
				unsigned char bitValue = switchValue & 0x1;
				if(bitValue == 0x0)
				{
					break;
				}
			}
			break;
		}
	}
}

void WaitTillSwitch2PressedAndReleased() //This function is making sure that Switch 2 is pressed and released
{
	unsigned char switchValue = 0;
	while(1)
	{
		switchValue = My_ReadSwitches();
		if(switchValue == 0x2)
		{
			while(1)
			{
				switchValue = My_ReadSwitches();
				unsigned char bitValue = switchValue & 0x2;
				if(bitValue == 0x0)
				{
					break;
				}
			}
			break;
		}
	}
}

void WaitTillSwitch3PressedAndReleased() //This function is making sure that Switch 3 is pressed and released
{
	unsigned char switchValue = 0;
	while(1)
	{
		switchValue = My_ReadSwitches();
		if(switchValue == 0x4)
		{
			while(1)
			{
				switchValue = My_ReadSwitches();
				unsigned char bitValue = switchValue & 0x4;
				if(bitValue == 0x0)
				{
					break;
				}
			}
			break;
		}
	}
}
