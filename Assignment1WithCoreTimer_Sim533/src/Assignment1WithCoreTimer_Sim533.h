/*****************************************************************************
 * Assignment1WithCoreTimer_Sim533.h
 *****************************************************************************/

#ifndef __ASSIGNMENT1WITHCORETIMER_SIM533_H__
#define __ASSIGNMENT1WITHCORETIMER_SIM533_H__

/* Add your custom header content here */
#include "../../ENCM511_SpecificFiles/ENCM511_include/CoffeePot_SimulatorFunctions2017.h"
#include <stdio.h>
#include <blackfin.h>
#include <sys/exception.h>

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

//Prototypes for Coffee Pot Assignment 1 Assembly Functions
extern "C" void demonstrateLEDASM(COFFEEPOT_DEVICE *coffeePot);
extern "C" void checkForCoffeePodASM(COFFEEPOT_DEVICE *coffeePot);

#endif /* __ASSIGNMENT1WITHCORETIMER_SIM533_H__ */
