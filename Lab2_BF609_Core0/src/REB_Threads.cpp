/*
 * REB_Threads.cpp
 *
 *  Created on: Nov 20, 2019
 *      Author: miche
 */
#include "REB_Threads.h"
#include "Lab2_BF609_Core0_uTTCOSg2017_main.h"

void REBThread1(void)
{
//REB Thread 1: Task that counts from 0 – 15 in ¼ second intervals and displays on REB LEDS 4 – 7
//Use 4 – 7 as these are not hidden behind 50 pin cable as a 0 - 3
	static unsigned short Thread1_Counter = 0;

	if(Thread1_Control)
	{
		My_Write_GPIO_REB_OutputASM(Thread1_Counter);
		printf("Writing numbers 0-15\n");
	}

	Thread1_Counter++;

	if (Thread1_Counter == 16)
		Thread1_Counter = 0;
}


void REBThread2(void)
{
//Task that ON COMMAND will read REB switches 0 – 3 and store them in an array the number of values
//must be changeable at demo time (no more than 100)
//Must be user and power friendly (meaning respond to request to store values in a humanly useful time, but does
//not run so often that wastes batter power
//As in Lab 1 – FP SW5 and SW4 are available to help control this task
	unsigned short int switchPattern = My_Read_GPIO_REB_InputASM();

	//write to the array if switch 4 is pressed
	if((myReadFrontPanelSwitches() & FP_SW4_ON) == FP_SW4_ON)
	{
		hardWareArray[array_index] = switchPattern;
		array_index++;
		printf("\n read pattern \n");

	}

	//terminate thread if writing is done by pressing switch 5 or going over 100 values
	if((myReadFrontPanelSwitches() & FP_SW5_ON) == FP_SW5_ON ||array_index >= 100)
	{
		Thread1_Control = false;
		printf("\ngoing into thread 3\n");
	}
}

void REBThread3(void)
{
	if(!Thread1_Control)
	{
		static int index = 0;
		printf("printing index %d\n", index);
		My_Write_GPIO_REB_OutputASM(hardWareArray[index]);
		index++;

		//Will exit this thread if it has gone through entire hardware array or if switch 2 is pressed
		if(array_index <= index || myReadFrontPanelSwitches() == FP_SW2_ON )
		{
			// reset
			index = 0;
			array_index = 0;
			Thread1_Control = true;
		}
	}
}
