/*
 * Lab4Main.cpp
 *
 *  Created on: Nov 28, 2019
 *      Author: aidan
 */
#include "Lab4_BF609_Core0.h"

#define THERMALSENSOR10PERCENT 0
#define SPI10PERCENT 0
#define SECOND 480000000
#define LLSW8	0x100

void startLab4(void)
{
	unsigned short int count = 0;

	Init_REB_SPI();
	Start_REB_SPI();
	while(REB_SPI_Ready() == false);

	Init_GP_Timer(3);
	Start_GP_Timer(3);

	unsigned long long int T1;
	unsigned long long int T2;
	unsigned long long int temperature;
	IsReady_GP_Timer(3);

	initializeLCD();
	writingPrelabMessage();

	#if THERMALSENSOR10PERCENT
		while(1)
		{
			T2 = ReadWidth_GP_Timer(3);
			T1 = (ReadPeriod_GP_Timer(3) - T2);
			temperature = 235 - ((400*T1)/T2);
			REB_Write_SPI(temperature);
		}
	#endif

	#if SPI10PERCENT
		while(1)
		{
			while(REB_SPI_Ready())
			{
				REB_Write_SPI(count);
				count++;
			}
		}
	#endif

}

void initializeLCD(void)
{
	unsigned long int timeWaited = (SECOND*0.01);
	unsigned long int value = 0;

	value = value | LLSW8; //setting logic lab switch 8 to high
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value | 0x30;
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value & 0xfeff;
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value | LLSW8;
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value & 0xfeff;
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value | LLSW8;
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value | 0x003c;
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value & 0xfeff;
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value | LLSW8;
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value & 0xff0f;
	value = value | 0x000f;
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value & 0xfeff;
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value | LLSW8;
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value & 0xff00;
	value = value | 0x0001;
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value & 0xfeff;
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value | LLSW8;
	REB_Write_SPI(value);
	waitABit(timeWaited);
}

void waitABit(unsigned long int timeValue)
{
	while(timeValue)
	{
		timeValue--;
	}
}

void writingPrelabMessage(void)
{
	unsigned long int timeWaited = (SECOND*0.01);
	unsigned long int value = 0;

	value = value & 0xff00; //Clearing the bits
	value = value | 0x0400; //setting logic lab switch 10 to high

	value = value | 0x20; //This is ascii space
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value & 0xfeff;
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value | LLSW8;
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value & 0xfeff;
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value | LLSW8;
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value & 0xff00;
	value = value | 0x35; //This is 5
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value & 0xfeff;
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value | LLSW8;
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value & 0xff00;
	value = value | 0x31; //This is 1
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value & 0xfeff;
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value | LLSW8;
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value & 0xfeff;
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value | LLSW8;
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value & 0xff00;
	value = value | 0x20; //This is ascii space
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value & 0xfeff;
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value | LLSW8;
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value & 0xfeff;
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value | LLSW8;
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value & 0xff00;
	value = value | 0x52; //This is R
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value & 0xfeff;
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value | LLSW8;
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value & 0xff00;
	value = value | 0x55; //This is U
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value & 0xfeff;
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value | LLSW8;
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value & 0xff00;
	value = value | 0x4c; //This is L
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value & 0xfeff;
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value | LLSW8;
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value & 0xff00;
	value = value | 0x53; //This is S
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value & 0xfeff;
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value | LLSW8;
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value & 0xff00;
	value = value | 0x20; //This is ascii space
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value & 0xfeff;
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value | LLSW8;
	REB_Write_SPI(value);
	waitABit(timeWaited);
}

void writingTemperature(unsigned long int temp)
{
	unsigned long int timeWaited = (SECOND*0.01);
	unsigned long int value = 0;
	unsigned long int tempValue = temp;

	value = value & 0xff00; //Clearing the bits
	value = value | 0x0400; //setting logic lab switch 10 to high
}

void writingInitials(void)
{

}

void writingTemperatureMessage(void)
{

}
