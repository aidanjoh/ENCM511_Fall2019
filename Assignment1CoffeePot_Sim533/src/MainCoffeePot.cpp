/*
 * MainCoffeePot.cpp
 *
 *  Created on: Oct 23, 2019
 *      Author: aidan
 */

#include "Assignment1CoffeePot_Sim533.h"

#define MAX_WATER_LEVEL 600
#define MAX_TEMPERATURE 100

#define NUMBEROFCOFFEEPOTS	4
#define SHOW_FUNCTION_STUB_INFORMATION 1

#define MASK_BITS_15TO2_AND_BIT0 0xfffd
#define MASK_LED 0xf000
#define MASK_BITS_15TO3_AND_BITS1TO0 0xfffb
#define MASK_BITS_15TO4_AND_BITS2TO0 0xfff7

#define WATERINFLOW 30
#define FULLHEATBOOST 15
#define HEATVALUE 190
#define TRUE 1
#define ZERO 0
#define TEMPERATURETOINSERTCOFFEEPOD 95

//ENUM for Coffeepot_ID to make it an array
COFFEEPOT_ID COFFEEPOTIDS[] = {COFFEEPOT1, COFFEEPOT2, COFFEEPOT3, COFFEEPOT4};

void startCoffeePot(void)
{
	showNameOfProcessorUsed();
	Init_CoffeePotSimulation(NUMBEROFCOFFEEPOTS, USE_TEXT_AND_GRAPHICS_GUIS); //Initializing the simulation

	char uniqueCoffeePot1to3Name[] = "Aidan";
	char uniqueCoffeePot4Name[] = "Aidanj";

	COFFEEPOT_DEVICE* coffeePotsBaseAddress[NUMBEROFCOFFEEPOTS];

	for (int j = ZERO; j < (NUMBEROFCOFFEEPOTS - 1); j++)
	{
		coffeePotsBaseAddress[j] = Add_CoffeePotToSystem_PlugAndPlay(COFFEEPOTIDS[j], uniqueCoffeePot1to3Name);
	}

	coffeePotsBaseAddress[3] = Add_CoffeePotToSystem_PlugAndPlay(COFFEEPOTIDS[3], uniqueCoffeePot4Name); //Making the fourth coffeepot have a different capacity

	initializingCoffeePot(coffeePotsBaseAddress);
	activateLEDControl(coffeePotsBaseAddress);
	activateWaterControl(coffeePotsBaseAddress);
	activateHeatControl(coffeePotsBaseAddress);

	while(TRUE)
	{
		for(int j = ZERO; j < NUMBEROFCOFFEEPOTS; j++)
		{
			//LEDControlDemo(coffeePotsBaseAddress);
			demonstrateLEDASM(coffeePotsBaseAddress[j]); //Using the ASM function instead
			fillCoffeePotToWaterLEvel(coffeePotsBaseAddress[j]);
			heatWaterToTemperature(coffeePotsBaseAddress[j]);
			checkForCoffeePodASM(coffeePotsBaseAddress[j]); //Using the ASM function instead
			//checkForCoffeePod(coffeePotsBaseAddress[j]);
		}
		FastForward_OneSimulationTIC(*coffeePotsBaseAddress);
	}

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

	printf("Aidan's Coffee pots are running on %s system \n", processor);

}

void initializingCoffeePot(COFFEEPOT_DEVICE *coffeePot[]) //This function will be activating the 4 different coffeepots
{
	unsigned short int currentControlRegister; //declaring a currentControlRegister variable

	for(int j = ZERO; j < NUMBEROFCOFFEEPOTS; j++)
	{
		currentControlRegister = ReadControlRegister_CPP(coffeePot[j]);
		unsigned short int newControlRegister = INITandSTAYPOWEREDON_BIT;
		coffeePot[j] -> controlRegister = newControlRegister;
	}

	for(int j = ZERO; j < NUMBEROFCOFFEEPOTS; j++)
	{
		while((currentControlRegister & DEVICE_READY_BIT_RO)!= DEVICE_READY_BIT_RO)
		{
			FastForward_OneSimulationTIC(coffeePot[j]);
			currentControlRegister = ReadControlRegister_CPP(coffeePot[j]);
		}
	}
}

void activateLEDControl(COFFEEPOT_DEVICE *coffeePot[])
{
	unsigned short int currentControlRegister;
	for(int j = ZERO; j < NUMBEROFCOFFEEPOTS; j++)
	{
		currentControlRegister = coffeePot[j] -> controlRegister;
		currentControlRegister = currentControlRegister & MASK_BITS_15TO2_AND_BIT0;
		currentControlRegister = currentControlRegister | LED_DISPLAY_ENABLE_BIT;
		coffeePot[j] -> controlRegister = currentControlRegister;
	}
	FastForward_OneSimulationTIC(*coffeePot);
}

void activateWaterControl(COFFEEPOT_DEVICE *coffeePot[])
{
	unsigned short int currentControlRegister;
	for (int j = ZERO; j < NUMBEROFCOFFEEPOTS; j++)
	{
		currentControlRegister = coffeePot[j] -> controlRegister;
		currentControlRegister = currentControlRegister & MASK_BITS_15TO3_AND_BITS1TO0;
		currentControlRegister = currentControlRegister | WATER_ENABLE_BIT;
		coffeePot[j] -> controlRegister = currentControlRegister;
	}
	FastForward_OneSimulationTIC(*coffeePot);
}

void activateHeatControl(COFFEEPOT_DEVICE *coffeePot[])
{
	unsigned short int currentControlRegister;

	for(int j = ZERO; j < NUMBEROFCOFFEEPOTS; j++)
	{
		currentControlRegister = coffeePot[j] -> controlRegister;
		currentControlRegister = currentControlRegister & MASK_BITS_15TO4_AND_BITS2TO0;
		currentControlRegister = currentControlRegister | HEATER_ENABLE_BIT;
		coffeePot[j] -> controlRegister = currentControlRegister;
	}

	FastForward_OneSimulationTIC(*coffeePot);
}

void LEDControlDemo(COFFEEPOT_DEVICE *coffeePot)
{
	unsigned short int currentControlRegister = coffeePot -> controlRegister;
	unsigned short int currentLEDState;

	currentLEDState = (currentControlRegister & MASK_LED) >> 12;

	switch(currentLEDState)
	{
	case 0:
		currentControlRegister = (currentControlRegister & ~MASK_LED) | LED1_BIT;
		break;
	case 1:
		currentControlRegister = (currentControlRegister & ~MASK_LED) | LED2_BIT;
		break;
	case 2:
		currentControlRegister = (currentControlRegister & ~MASK_LED) | LED3_BIT;
		break;
	case 4:
		currentControlRegister = (currentControlRegister & ~MASK_LED) | LED4_BIT;
		break;
	case 8:
		currentControlRegister = (currentControlRegister & ~MASK_LED) | LED1_BIT;
		break;
	}

	coffeePot -> controlRegister = currentControlRegister;
}

void fillCoffeePotToWaterLEvel(COFFEEPOT_DEVICE *coffeePot)
{
	unsigned short int currentControlRegister = coffeePot -> controlRegister;
	unsigned short int currentWaterLevel = CurrentWaterLevel_CPP(coffeePot);

	if (currentWaterLevel < MAX_WATER_LEVEL - (MAX_WATER_LEVEL/8))
	{
		coffeePot -> waterInFlowRegister = WATERINFLOW;
		currentControlRegister = currentControlRegister & MASK_BITS_15TO3_AND_BITS1TO0;
		currentControlRegister = currentControlRegister | WATER_ENABLE_BIT;
		coffeePot -> controlRegister = currentControlRegister;
	}
	else
	{
		coffeePot -> waterInFlowRegister = ZERO;
		currentControlRegister = currentControlRegister & ~WATER_ENABLE_BIT;
		coffeePot -> controlRegister = currentControlRegister;
	}
}

void heatWaterToTemperature(COFFEEPOT_DEVICE *coffeePot)
{
	unsigned short int currentControlRegister = coffeePot -> controlRegister;
	unsigned short int currentTemperature = CurrentTemperature_CPP(coffeePot);

	if(currentTemperature < MAX_TEMPERATURE)
	{
		coffeePot -> heaterRegister = HEATVALUE;
		coffeePot -> heaterBoostRegister = FULLHEATBOOST;
		currentControlRegister = currentControlRegister & MASK_BITS_15TO4_AND_BITS2TO0;
		currentControlRegister = currentControlRegister | HEATER_ENABLE_BIT;
		coffeePot -> controlRegister = currentControlRegister;
	}
	else
	{
		coffeePot -> heaterRegister = ZERO;
		coffeePot -> heaterBoostRegister = ZERO;
		currentControlRegister = currentControlRegister & ~HEATER_ENABLE_BIT;
		coffeePot -> controlRegister = currentControlRegister;
	}
}


void checkForCoffeePod(COFFEEPOT_DEVICE *coffeePot)
{
	unsigned short int currentControlRegister = coffeePot -> controlRegister;
	unsigned short int currentTemperature = CurrentTemperature_CPP(coffeePot);

	if (currentTemperature >= TEMPERATURETOINSERTCOFFEEPOD)
	{
		if((currentControlRegister & COFFEEPOT_INSERTED) == ZERO)
		{
			currentControlRegister = (currentControlRegister | COFFEEPOT_INSERTED);
			coffeePot -> controlRegister = currentControlRegister;
		}
	}
}
