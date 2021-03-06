/*****************************************************************************
 * Coffeepot_Sim533.cpp
 *****************************************************************************/

#include <sys/platform.h>
#include "adi_initialize.h"
#include "Coffeepot_Sim533.h"


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
	My_CoffeePot_Main_Aidan();
#endif

	/* Begin adding your custom code here */

	return 0;
}

