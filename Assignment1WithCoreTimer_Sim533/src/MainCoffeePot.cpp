/*
 * MainCoffeePot.cpp
 *
 *  Created on: Oct 23, 2019
 *      Author: aidan
 */

#include "Assignment1WithCoreTimer_Sim533.h"

#define MAX_WATER_LEVEL 600
#define MAX_TEMPERATURE 100

#define NUMBEROFCOFFEEPOTS	2
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

#define PERIOD 100000
#define COUNT 100000
#define DEBUG 0
#define TCNTLENABLETIMERBIT 0x00000002
#define TCNTLAUTORELOADBIT 0x00000004
#define TCNTLPOWERBIT 0x00000001

//ENUM for Coffeepot_ID to make it an array
COFFEEPOT_ID COFFEEPOTIDS[] = {COFFEEPOT1, COFFEEPOT2, COFFEEPOT3, COFFEEPOT4};

extern volatile bool doFastForward = false;

void startCoffeePot(void)
{
	showNameOfProcessorUsed();
	Init_CoffeePotSimulation(NUMBEROFCOFFEEPOTS, USE_TEXT_AND_GRAPHICS_GUIS); //Initializing the simulation

	char uniqueCoffeePot1Name[] = "Aidan";
	char uniqueCoffeePot2Name[] = "Aidanj";

	COFFEEPOT_DEVICE* coffeePotsBaseAddress[NUMBEROFCOFFEEPOTS];

	coffeePotsBaseAddress[0] = Add_CoffeePotToSystem_PlugAndPlay(COFFEEPOTIDS[0], uniqueCoffeePot1Name);
	coffeePotsBaseAddress[1] = Add_CoffeePotToSystem_PlugAndPlay(COFFEEPOTIDS[1], uniqueCoffeePot2Name); //Making the second coffeepot have a different capacity

	myInit_CoreTimer(PERIOD, COUNT); //This is initializing the Core Timer
	register_handler(ik_timer, interruptServiceRoutineFastForward);
	myControl_CoreTimer((TCNTLENABLETIMERBIT | TCNTLAUTORELOADBIT |TCNTLPOWERBIT)); //This is enabling the Core Timer
	startCoreTimerInterrupts();

	initializingCoffeePot(coffeePotsBaseAddress);
	activateLEDControl(coffeePotsBaseAddress);
	activateWaterControl(coffeePotsBaseAddress);
	activateHeatControl(coffeePotsBaseAddress);



	bool isCoreTimerComplete;
	isCoreTimerComplete = myCompleted_CoreTimer();

	#if DEBUG
		printf("%d \n", isCoreTimerComplete);
	#endif

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
		if(doFastForward)
		{
			FastForward_OneSimulationTIC(*coffeePotsBaseAddress);
			doFastForward = false;
		}
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
			if(doFastForward)
			{
				FastForward_OneSimulationTIC(coffeePot[j]);
				doFastForward = false;
			}
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
	if(doFastForward)
	{
		FastForward_OneSimulationTIC(*coffeePot);
		doFastForward = false;
	}
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
	if(doFastForward)
	{
		FastForward_OneSimulationTIC(*coffeePot);
		doFastForward = false;
	}
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
	if(doFastForward)
	{
		FastForward_OneSimulationTIC(*coffeePot);
		doFastForward = false;
	}
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

#define CORETIMEPOWERBIT 0x00000001
#define CORETIMERAUTORLD 0x00000008

void myInit_CoreTimer(unsigned long int period, unsigned long int count)
{
	*pTCNTL = CORETIMEPOWERBIT; //Might have to include the autorelod bit or with the power bit
	*pTPERIOD = period; //Setting period after count to make sure count does not get overwritten
	*pTCOUNT = count; //Setting the count registers which counts down to 0 every cycle and causes the control register bit 3 to turn on when 0
	*pTSCALE = 0x00000000; //Setting the scale register to 0

	#if DEBUG
		printf("Core Timer Control Register %lu \n", *pTCNTL);
		printf("Core Timer Period Register %lu \n", *pTPERIOD);
		printf("Core Timer Count Register %lu \n", *pTCOUNT);
		printf("Core Timer Scale Register %lu \n", *pTSCALE);
	#endif
}

#define TCNTLBIT3TO0 0x0000000f

void myControl_CoreTimer(unsigned short int cntrl_value)
{

	cntrl_value = cntrl_value & TCNTLBIT3TO0;
	*pTCNTL = cntrl_value;
}

#define TCNTLBITS3AND1TO0 0x0000000b
#define TCNTLDONEBIT 0x00000008

bool myCompleted_CoreTimer(void)
{
	bool returnValue = false;
	unsigned long int coreTimerControlValue = *pTCNTL;

	if((coreTimerControlValue & TCNTLBITS3AND1TO0) == TCNTLBITS3AND1TO0)
	{
		*pTCNTL = *pTCNTL & (~TCNTLDONEBIT);
		returnValue = true;
	}

	return returnValue;
}

void myTimedWaitOnCoreTimer(void)
{
	bool coreTimerInitialized = false;
	int count = 0;

	while(!coreTimerInitialized)
	{
		unsigned long int stickyBitTCNTL = (*pTCNTL & TCNTLDONEBIT);
		if(TCNTLDONEBIT == stickyBitTCNTL)
		{
			coreTimerInitialized = true;
		}
	count++;

	#if DEBUG
		printf("Time through loop %d \n", count);
	#endif

	}

	return;
}

#define TCNTLTINTBIT 0x00000008
#define TCNTLTMRENBIT 0x00000002

void startCoreTimer(void)
{
	unsigned long int cntrl_value = TCNTLTMRENBIT;
	*pTCNTL = (*pTCNTL | cntrl_value);
}

void stopCoreTimer(void)
{
	unsigned long int cntrl_value = (~TCNTLTMRENBIT);
	*pTCNTL = (*pTCNTL & (cntrl_value));
}

void resetCoreTimerInterrupt(void)
{
	*pTCNTL = *pTCNTL & (~TCNTLTINTBIT);
}

#define CORETIMERIMASKBITINTERRUPT 0x00000040

#pragma interrupt
void interruptServiceRoutineFastForward(void)
{
	#if DEBUG
		printf("In interrupt Function \n");
	#endif
	unsigned long int coreTimerControlValue = *pTCNTL;
	*pTCNTL = coreTimerControlValue & (~TCNTLDONEBIT); //Reseting the Core Timer

	//unsigned long int coreInteruptMaskRegister = *pIMASK;
	//*pIMASK = coreInteruptMaskRegister & (~CORETIMERIMASKBITINTERRUPT); //Clearing the interrupt coretimer bit
	doFastForward = true;

	ssync(); //Making sure all the instructions have been flushed
}

void startCoreTimerInterrupts(void)
{
	unsigned long int coreInteruptMaskRegister = *pIMASK;
	//This is sotring the address of the function that the interrupt will go to
	//in the vector event table
	//*pEVT6 = (void*) interruptServiceRoutineFastForward;
	*pIMASK = coreInteruptMaskRegister | CORETIMERIMASKBITINTERRUPT; //This is enabling the core timer interupt bit in the IMASK register

	//OR
	//register_handler(ik_timer,interruptServiceRoutineFastForward);

}

void stopCoreTimerInterrupts(void)
{
	unsigned long int coreInteruptMaskRegister = *pIMASK;
	*pIMASK = coreInteruptMaskRegister & (~CORETIMERIMASKBITINTERRUPT); //Disabling the coretimer IMASK interrupt Bit
}
