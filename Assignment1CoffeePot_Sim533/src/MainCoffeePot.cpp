/*
 * MainCoffeePot.cpp
 *
 *  Created on: Oct 23, 2019
 *      Author: aidan
 */

#include "Assignment1CoffeePot_Sim533.h"

#define MAX_SECONDS 10
#define MAX_WATER_LEVEL 600
#define MAX_TEMPERATURE 80

#define NUMBEROFCOFFEEPOTS	1
#define SHOW_FUNCTION_STUB_INFORMATION 1

void startCoffeePot(void)
{
	showNameOfProcessorUsed();

	Init_CoffeePotSimulation(NUMBEROFCOFFEEPOTS, USE_TEXT_AND_GRAPHICS_GUIS); //Initializing the simulation


	char uniqueCoffeePot1Name[] = "Aidan";
	char uniqueCoffeePot2Name[] = "Aidan Johnson";

	COFFEEPOT_DEVICE *coffeePot1BaseAddress = 0;
	COFFEEPOT_DEVICE *coffeePot2BaseAddress = 0;

	coffeePot1BaseAddress = Add_CoffeePotToSystem_PlugAndPlay(COFFEEPOT1, uniqueCoffeePot1Name);
	//coffeePot2BaseAddress = Add_CoffeePotToSystem_PlugAndPlay(COFFEEPOT2, uniqueCoffeePot2Name);

	bool continueDemonstrateLEDControl = true;
	unsigned long int secondsCounter = 0;
/*
	while(continueDemonstrateLEDControl)
	{

	}
*/

}


inline void Show_Function_Stub_Information(char *functionNameInformation)
{
	if(SHOW_FUNCTION_STUB_INFORMATION)
		printf("%s \n", functionNameInformation);
}


void showNameOfProcessorUsed(void) //This function is displaying what processor is being used
{
#if defined(__ADSPBF533__)
	char processor[] = "__ADSPBF533__";
#else
	char processor[] = "__ADSOBF609__";
#endif

	printf("Aidan's Coffee pot running on %s system \n", processor);

}
