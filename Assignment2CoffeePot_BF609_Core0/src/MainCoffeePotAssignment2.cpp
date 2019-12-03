/*
 * MainCoffeePotAssignment2.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: aidan
 */
#include "Assignment2CoffeePot_BF609_Core0.h"

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

#define PERIOD 480000000
#define COUNT 480000000
#define DEBUG 0
#define TCNTLENABLETIMERBIT 0x00000002
#define TCNTLAUTORELOADBIT 0x00000004
#define TCNTLPOWERBIT 0x00000001
#define CONTROLREGISTERCONTRILBITSMASK 0x000F

//ENUM for Coffeepot_ID to make it an array
COFFEEPOT_ID COFFEEPOTIDS[] = {COFFEEPOT1, COFFEEPOT2, COFFEEPOT3, COFFEEPOT4};

extern volatile bool doFastForward = false;
bool My_Init_LEDInterface_Done = false;
bool My_Init_SwitchInterface_Done = false;
bool My_Init_GPIO_REB_Input_Done = false;
bool My_Init_GPIO_REB_Output_Done = false;
bool My_Init_GPIO_REB_Done = false;
static bool FPSW5PressedAndReleased = false;

void startCoffeePot(void)
{
	showNameOfProcessorUsed();
	Init_CoffeePotSimulation(NUMBEROFCOFFEEPOTS, USE_TEXT_AND_GRAPHICS_GUIS); //Initializing the simulation

	char uniqueCoffeePot1Name[] = "Aidan";
	char uniqueCoffeePot2Name[] = "Aidanj";

	COFFEEPOT_DEVICE* coffeePotsBaseAddress[NUMBEROFCOFFEEPOTS];

	coffeePotsBaseAddress[0] = Add_CoffeePotToSystem_PlugAndPlay(COFFEEPOTIDS[0], uniqueCoffeePot1Name);
	coffeePotsBaseAddress[1] = Add_CoffeePotToSystem_PlugAndPlay(COFFEEPOTIDS[1], uniqueCoffeePot2Name); //Making the second coffeepot have a different capacity

	My_Init_SwitchInterface();  //This function is initiating the switches on the panel
	My_Init_GPIO_REB_Input(); //This function is initiating the switches on the board
	My_Init_LEDInterface();  //This function is initiating the LEDS on the panel
	My_Init_GPIO_REB_Output(); //This function is initiating the LEDs on the board

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
			//demonstrateLEDASM(coffeePotsBaseAddress[j]); //Using the ASM function instead
			fillCoffeePotToWaterLEvel(coffeePotsBaseAddress[j]);
			heatWaterToTemperature(coffeePotsBaseAddress[j]);
			checkForCoffeePodASM(coffeePotsBaseAddress[j]); //Using the ASM function instead
			//checkForCoffeePod(coffeePotsBaseAddress[j]);
		}

		WaitTillSwitch5PressedAndReleased();
		if(FPSW5PressedAndReleased == true)
		{
			coffeePot1OverWritingControlRegisterBits(coffeePotsBaseAddress[0]);
			coffeePot2OverWritingControlRegisterBits(coffeePotsBaseAddress[1]);
		}

		showingCoffeePot1LEDSOnFrontPanelAndSimulationLEDS(coffeePotsBaseAddress[0]);
		showingCoffeePot2LEDSOnREBAndSimulationLEDS(coffeePotsBaseAddress[1]);

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

	if (currentWaterLevel < MAX_WATER_LEVEL - (MAX_WATER_LEVEL/3))
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

void showingCoffeePot1LEDSOnFrontPanelAndSimulationLEDS(COFFEEPOT_DEVICE *coffeePot)
{
	unsigned short int currentControlRegister = coffeePot -> controlRegister;
	unsigned short int coffeePot1LEDS;

	coffeePot1LEDS = (currentControlRegister & CONTROLREGISTERCONTRILBITSMASK);

	Write_GPIO_FrontPanelLEDS(coffeePot1LEDS);

	coffeePot1LEDS = coffeePot1LEDS << 12;
	currentControlRegister = ((~MASK_LED) & currentControlRegister);

	coffeePot -> controlRegister = (coffeePot1LEDS | currentControlRegister);
}

void showingCoffeePot2LEDSOnREBAndSimulationLEDS(COFFEEPOT_DEVICE *coffeePot)
{
	unsigned short int currentControlRegister = coffeePot -> controlRegister;
	unsigned short int coffeePot2LEDS;

	coffeePot2LEDS = (currentControlRegister & CONTROLREGISTERCONTRILBITSMASK);


	My_Write_REB_LED(coffeePot2LEDS);

	coffeePot2LEDS = coffeePot2LEDS << 12;

	currentControlRegister = ((~MASK_LED) & currentControlRegister);

	coffeePot -> controlRegister = (coffeePot2LEDS | currentControlRegister);
}

void My_Write_REB_LED(unsigned short int LEDValue) //This function is writing the values for the REB LEDs
{
	//printf("Stub for My_Write_REB_LED() \n");

	if (My_Init_GPIO_REB_Output_Done == false) // My_Init_GPIO_REB_Output_Done for his function
	{
		printf("LED hardware not ready \n");
		return;
	}
	#ifdef __ADSPBF609__
		My_Write_GPIO_REB_OutputASM(LEDValue);
	#endif
}

#define CONTROLREGISTERCONTROLBITSMASK 0x000f

void coffeePot1OverWritingControlRegisterBits(COFFEEPOT_DEVICE *coffeePot)
{
	unsigned short int currentControlRegister = coffeePot -> controlRegister;
	unsigned short int switchValue = My_ReadSwitches();

	currentControlRegister = (currentControlRegister & (~CONTROLREGISTERCONTROLBITSMASK));
	coffeePot -> controlRegister = (currentControlRegister | switchValue);
}

void coffeePot2OverWritingControlRegisterBits(COFFEEPOT_DEVICE *coffeePot)
{
	unsigned short int currentControlRegister = coffeePot -> controlRegister;
	unsigned short int switchValue = My_Read_REB_Switches();

	currentControlRegister = (currentControlRegister & (~CONTROLREGISTERCONTROLBITSMASK));
	coffeePot -> controlRegister = (currentControlRegister | switchValue);
}

unsigned short int My_Read_REB_Switches(void)
{
		if(My_Init_GPIO_REB_Input_Done == false) //My_Init_GPIO_REB_Input_Done for his function
		{
			printf("Switch hardware not ready \n");
			return -1;
		}

		REB_BITS16 wantedSwitchOnBoardValueActiveHigh = My_Read_GPIO_REB_InputASM(); //The board is active high
		return wantedSwitchOnBoardValueActiveHigh;
}

unsigned char My_ReadSwitches(void) //This function is reading the switches from the panel
{
			if (My_Init_SwitchInterface_Done == false)
			{
				printf("Switch hardware not ready \n");
				return -1;
			}

			FRONTPANEL_SWITCH_5BIT_VALUE activeLowValues = Read_GPIO_FrontPanelSwitches();
			FRONTPANEL_SWITCH_5BIT_VALUE activeHighValues = ~activeLowValues;


			#define MASK_KEEP_LOWER_FIVE_BITS 0x1F // use bit-wise
			FRONTPANEL_SWITCH_5BIT_VALUE wantedSwitchValueActiveHigh = activeHighValues & MASK_KEEP_LOWER_FIVE_BITS;
			return wantedSwitchValueActiveHigh;

}

#define FRONTPANELSW5 0x10
void WaitTillSwitch5PressedAndReleased() //This function is making sure that Switch 3 is pressed and released
{
	unsigned char switchValue;

	switchValue = My_ReadSwitches();
	if((switchValue == FRONTPANELSW5) && (!FPSW5PressedAndReleased))
	{
		while(1)
		{
			switchValue = My_ReadSwitches();
			unsigned char bitValue = switchValue & FRONTPANELSW5;
			if(bitValue == 0x0)
			{
				FPSW5PressedAndReleased = true;
				return;
			}
		}
	}
	else
	{
		return;
	}
}
