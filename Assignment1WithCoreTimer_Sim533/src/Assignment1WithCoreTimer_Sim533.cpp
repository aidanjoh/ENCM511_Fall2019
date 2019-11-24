/*****************************************************************************
 * Assignment1WithCoreTimer_Sim533.cpp
 *****************************************************************************/

#include <sys/platform.h>
#include "adi_initialize.h"
#include "Assignment1WithCoreTimer_Sim533.h"

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

