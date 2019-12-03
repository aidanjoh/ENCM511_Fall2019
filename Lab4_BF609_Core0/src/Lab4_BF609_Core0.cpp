/*****************************************************************************
 * Lab4_BF609_Core0.cpp
 *****************************************************************************/

#include <sys/platform.h>
#include <sys/adi_core.h>
#include <ccblkfn.h>
#include "adi_initialize.h"
#include "Lab4_BF609_Core0.h"
#include "../../ENCM511_SpecificFiles/ENCM511_include/REB_SPI_Library.h"
#include "../../ENCM511_SpecificFiles/ENCM511_include/GP_Timer_Library.h"

/** 
 * If you want to use command program arguments, then place them in the following string. 
 */
char __argv_string[] = "";

int main(int argc, char *argv[])
{
	/**
	 * Initialize managed drivers and/or services that have been added to 
	 * the project.
	 * @return zero on success 
	 */
	adi_initComponents();
	
	/**
	 * The default startup code does not include any functionality to allow
	 * core 0 to enable core 1. A convenient way to enable
	 * core 1 is to use the adi_core_enable function. 
	 */
	adi_core_enable(ADI_CORE_1);

	/* Begin adding your custom code here */
	unsigned short int count = 0;

	Init_REB_SPI();
	Start_REB_SPI();
	Init_GP_Timer(3);
	Start_GP_Timer(3);
	unsigned long long int T1;
	unsigned long long int T2;
	unsigned long long int temperature;
	IsReady_GP_Timer(3);

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




	return 0;
}

