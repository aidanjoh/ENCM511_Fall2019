/*****************************************************************************
 * Lab0_BF533_MOCKEDLEDandSwitches.cpp
 *****************************************************************************/

#include <sys/platform.h>
#include "adi_initialize.h"
#include "Lab0_BF533_MOCKEDLEDandSwitches.h"
#include <stdio.h>


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
	printf("Start BF533 Lab 0\n");
	Start_Lab0();
#endif

#ifdef __ADSPBF609__
	printf("Start BF609 Lab 0\n");
	Start_Lab0();
#endif


	/* Begin adding your custom code here */

	return 0;
}

