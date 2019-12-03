/*****************************************************************************
 * Assignment2CoffeePot_BF609_Core0.h
 *****************************************************************************/

#ifndef __ASSIGNMENT2COFFEEPOT_BF609_CORE0_H__
#define __ASSIGNMENT2COFFEEPOT_BF609_CORE0_H__

/* Add your custom header content here */
#include "../../ENCM511_SpecificFiles/ENCM511_include/CoffeePot_SimulatorFunctions2017.h"
#include <stdio.h>
#include <blackfin.h>
#include <sys/exception.h>
#include "Lab1And0FrontPanelFunctions.h"
#include "../../ENCM511_SpecificFiles/ENCM511_include/FrontPanel_LED_Switches.h"
#include "../../ENCM511_SpecificFiles/ENCM511_include/REB_GPIO_Input_library.h"
#include "../../ENCM511_SpecificFiles/ENCM511_include/REB_GPIO_Output_library.h"

//Prototypes for Coffee Pot Assignment 1 Functions
void startCoffeePot(void);
void showNameOfProcessorUsed(void);
void DemonstrateLEDControl_CPP(void);
void initializingCoffeePot(COFFEEPOT_DEVICE* coffeePot[]);
void activateLEDControl(COFFEEPOT_DEVICE *coffeePot[]);
void activateWaterControl(COFFEEPOT_DEVICE *coffeePot[]);
void activateHeatControl(COFFEEPOT_DEVICE *coffeePot[]);
void LEDControlDemo(COFFEEPOT_DEVICE *coffeePot);
void fillCoffeePotToWaterLEvel(COFFEEPOT_DEVICE *coffeePot);
void heatWaterToTemperature(COFFEEPOT_DEVICE *coffeePot);
void checkForCoffeePod(COFFEEPOT_DEVICE *coffeePot);

//Prototypes for CoreTimer Functions for BF533
void myInit_CoreTimer(unsigned long int period, unsigned long int count);
void myControl_CoreTimer(unsigned short int cntrl_value);
bool myCompleted_CoreTimer(void);
void myTimedWaitOnCoreTimer(void);
void startCoreTimer(void);
void stopCoreTimer(void);
void resetCoreTimerInterrupt(void);

//Prototypes for Interrupt Functions
void interruptServiceRoutineFastForward(void);
void startCoreTimerInterrupts(void);
void stopCoreTimerInterrupts(void);

//Prototypes for Requirement1
void showingCoffeePot1LEDSOnFrontPanelAndSimulationLEDS(COFFEEPOT_DEVICE *coffeePot);
void showingCoffeePot2LEDSOnREBAndSimulationLEDS(COFFEEPOT_DEVICE *coffeePot);

//Prototypes for Requirement2
void coffeePot1OverWritingControlRegisterBits(COFFEEPOT_DEVICE *coffeePot);
void coffeePot2OverWritingControlRegisterBits(COFFEEPOT_DEVICE *coffeePot);

//These variables are all declared and initialized to be false to begin until the respective function is called
//to initialize the respective equipment
extern bool My_Init_SwitchInterface_Done;
extern bool My_Init_LEDInterface_Done;
extern bool My_Init_GPIO_REB_Input_Done;
extern bool My_Init_GPIO_REB_Output_Done;
extern bool My_Init_GPIO_REB_Done;

//Function Prototypes
void My_Init_SwitchInterface(void);
void My_Init_LEDInterface(void);
void My_Init_GPIO_REB_Input(void);
void My_Init_GPIO_REB_Output(void);
void My_Write_REB_LED(unsigned short int);
unsigned char My_ReadSwitches(void);
unsigned short int My_Read_REB_Switches(void);
void WaitTillSwitch5PressedAndReleased(void);

//Prototypes for Coffee Pot Assignment 1 Assembly Functions as well as from Lab 1
extern "C" void demonstrateLEDASM(COFFEEPOT_DEVICE *coffeePot);
extern "C" void checkForCoffeePodASM(COFFEEPOT_DEVICE *coffeePot);
extern "C" unsigned long long int ReadProcessorCyclesASM(void);
extern "C" void My_Write_GPIO_REB_OutputASM(unsigned short int);
extern "C" unsigned short int My_Read_GPIO_REB_InputASM(void);
extern "C" void My_Init_GPIO_REB_InputASM(void);
extern "C" void My_Init_GPIO_REB_OutputASM(void);

#endif /* __ASSIGNMENT2COFFEEPOT_BF609_CORE0_H__ */
