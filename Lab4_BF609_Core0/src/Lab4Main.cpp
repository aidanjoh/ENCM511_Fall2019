/*
 * Lab4Main.cpp
 *
 *  Created on: Nov 28, 2019
 *      Author: aidan
 */
#include "Lab4_BF609_Core0.h"

void startLab4(void)
{
	unsigned short int count = 0;

	Init_REB_SPI();
	Start_REB_SPI();
	Init_GP_Timer(3);
	Start_GP_Timer(3);

	unsigned long long int T1;
	unsigned long long int T2;
	unsigned long long int temperature;
	IsReady_GP_Timer(3);

	/*
	while(1)
	{
		T2 = ReadWidth_GP_Timer(3);
		T1 = (ReadPeriod_GP_Timer(3) - T2);
		temperature = 235 - ((400*T1)/T2);
		REB_Write_SPI(temperature);
	}

	while(1)
	{
		while(REB_SPI_Ready())
		{
			REB_Write_SPI(count);
			count++;
		}
	}
	*/

}
