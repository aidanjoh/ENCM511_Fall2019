/*****************************************************************************
 * Assignment2CoffeePot_BF609_Core0.cpp
 *****************************************************************************/

#include <sys/platform.h>
#include <sys/adi_core.h>
#include <ccblkfn.h>
#include "adi_initialize.h"
#include "Assignment2CoffeePot_BF609_Core0.h"

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

	#ifdef __ADSPBF533__
		printf("Starting the Coffee Pot Assignment\n");
		startCoffeePot();
	#endif

	#ifdef __ADSPBF609__
		printf("Starting the Coffee Pot Assignment\n");
		startCoffeePot();
	#endif

	return 0;
}

