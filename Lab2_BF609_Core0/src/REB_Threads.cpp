/*
 * REB_Threads.cpp
 *
 *  Created on: Nov 20, 2019
 *      Author: miche
 */
#include "REB_Threads.h"

//This bool is so that another thread can control if Thread 1 writes to the LEDS
static bool Thread1_Control = true;

void REBThread1(void)
{
//REB Thread 1: Task that counts from 0 – 15 in ¼ second intervals and displays on REB LEDS 4 – 7
//Use 4 – 7 as these are not hidden behind 50 pin cable as a 0 - 3
	static unsigned short Thread1_Counter = 0;

	if(Thread1_Control)
		My_Write_GPIO_REB_OutputASM(Thread1_Counter);

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




}

void REBThread3(void)
{





}
