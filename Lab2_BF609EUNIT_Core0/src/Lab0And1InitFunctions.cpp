/*
 * Lab0And1InitFunctions.cpp
 *
 *  Created on: Nov 21, 2019
 *      Author: aidan
 */
#include "Lab2EUNITTesting.h" //Will need to change this

//Global Variables


void My_Init_SwitchInterface(void) //This function is initializing the Switches on the Front Panel
{
	My_Init_SwitchInterface_Done = true;
	#ifdef __ADSPBF609__
		Init_GPIO_FrontPanelSwitches();
	#endif
}

void My_Init_LEDInterface(void) //This function is initializing the LEDs on the Front Panel
{
	My_Init_LEDInterface_Done = true;
	#ifdef __ADSPBF609__
		Init_GPIO_FrontPanelLEDS();
	#endif

}

void My_Init_GPIO_REB_Input(void) //This function is initializing the switches on the REB
{
	My_Init_GPIO_REB_Input_Done = true;

	#ifdef __ADSPBF609__
			My_Init_GPIO_REB_InputASM();
	#endif
}

void My_Init_GPIO_REB_Output(void) //This function is initializing the LEDs on the REB
{
	My_Init_GPIO_REB_Output_Done = true;

	#ifdef __ADSPBF609__
			My_Init_GPIO_REB_OutputASM();
	#endif
}
