/*
 * Lab1_GeneralCode.cpp
 *
 *  Created on: Oct 8, 2019
 *      Author: aidan
 */

#include <sys/platform.h>
#include "adi_initialize.h"
#include "Lab1_BF609_Core0.h"

#define GARBAGE_VALUE static_cast<unsigned char>(-1) //The garbage value is unsigned -1

//These variables are all declared and initialized to be false to begin until the respective function is called
//to initialize the respective equipment

static bool My_Init_SwitchInterface_Done = false;
static bool My_Init_LEDInterface_Done = false;
static bool My_Init_GPIO_REB_Input_Done = false;
static bool My_Init_GPIO_REB_Output_Done = false;

//Given the variable lastLEDValueWritten a garbage value to start
static unsigned char lastLEDValueWritten = GARBAGE_VALUE;

//Underneath is the code stub for Start Lab1
void Start_Lab1(void)
{
	printf("Here in Start_Lab1\n"); //This is declaring it is the start of Lab 1

	//unsigned char switchValueBad = My_ReadSwitches();

	My_Init_SwitchInterface();  //This function is initiating the switches on the panel
	My_Init_GPIO_REB_Input(); //This function is initiating the switches on the board

#if 1
	My_Init_LEDInterface();  //This function is initiating the LEDS on the panel
	My_Init_GPIO_REB_Output(); //This function is initiating the LEDs on the board

	printf("Press Switch 1\n"); //Pressing Switch 1 will initiate the Start of the Lab

	WaitTillSwitch1PressedAndReleased(); //This function is in place to make sure that switch 1 was pressed and then released

	//The array below holds the hex values for my initials
	unsigned char intials[15] = {0x00, 0xe0, 0x1c, 0x13, 0x1c, 0xe0, 0x00, 0xc0, 0x00, 0xe0, 0xc3, 0xff, 0x03, 0x00, 0xc0};

	int count = 0; //Creating a counter value
	unsigned char switchValue = 0; //Creating a value to hold the switch Value

	//Switch 1 has a value of: 0x01
	//Switch 2 has a value of: 0x02
	//Switch 3 has a value of: 0x04
	//Switch 4 has a value of: 0x08

	unsigned long long int initialTime; //This variable will hold the initial Time
	unsigned long long int WaitTime = 480000000; //The wait time was selected to be 1 second which is equal to 480000000 processor cycles
	unsigned long long int time; //This variable will hold the time


	while(1)
	{
		initialTime = ReadProcessorCyclesASM();
		My_WriteLED(intials[count]); //printing initials line by line
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
		while(time < initialTime + WaitTime)
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
}

unsigned char My_ReadSwitches(void) //This function is reading the switches from the panel
{
	printf("Stub for My_ReadSwitches()\n");

	#ifdef __ADSPBF609__
		#if 1
			if(My_Init_GPIO_REB_Input_Done == false)
			{
				printf("Switch hardware not ready \n");
				return GARBAGE_VALUE;
			}

			REB_BITS16 activeHighValues = Read_GPIO_REB_Input(); //The board is active high

			#define MASK_KEEP_BITS_11_TO_8 0x0f00
			REB_BITS16 wantedSwitchOnBoardValueActiveHigh = activeHighValues & MASK_KEEP_BITS_11_TO_8;
			wantedSwitchOnBoardValueActiveHigh = wantedSwitchOnBoardValueActiveHigh >> 8;
			return wantedSwitchOnBoardValueActiveHigh;
		#endif

		#if 0

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
		#endif
	#else
		return 0x55;
	#endif

}

unsigned char My_ReadLED(void) //This function is returning the last LED value written
{
	//printf("Stub for My_ReadLED()\n");
	return lastLEDValueWritten;
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

	unsigned char binaryArray[9]; //Char array holding the values to print out
	charToBinary(neededLEDValue, binaryArray); //Calling the char to binary function
	Write_GPIO_FrontPanelLEDS(neededLEDValue); //Writing the value to the panel of LEDs

	// TODO will have to add the writing to board instead
	lastLEDValueWritten = neededLEDValue; //Putting the last LED value into the appropriate variable

#else //This is for the 533 emulator
	//Char array holding the values to print out
	unsigned char binaryArray[9];
	charToBinary(neededLEDValue, binaryArray); //Function converting the char to binary using the array holding the values
	printf("LED value - decimal %3d; hex 0x%2x; bit pattern %s \n", neededLEDValue, neededLEDValue, &binaryArray);
	lastLEDValueWritten = neededLEDValue;
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
	//printf("Stub for My_Init_GPIO_BoardLEDS() \n");
	My_Init_GPIO_REB_Input_Done = true;

	#ifdef __ADSPBF609__
		Init_GPIO_REB_Input();
	#endif
}

void My_Init_GPIO_REB_Output(void) //This function is initializing the LEDs on the Board
{
	//printf("Stub for My_Init_GPIO_BoardSwitches");
	My_Init_GPIO_REB_Output_Done = true;

	#ifdef __ADSPBF609__
		Init_GPIO_REB_Output();
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

void WaitTillSwitch1PressedAndReleased() //This function is making sure that Switch 1 is pressed and released
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

void WaitTillSwitch2PressedAndReleased() //This function is making sure that Switch 2 is pressed and released
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

void WaitTillSwitch3PressedAndReleased() //This function is making sure that Switch 3 is pressed and released
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
