/*****************************************************************************
 * Assignment1CoffeePot_Sim533.h
 *****************************************************************************/

#ifndef __ASSIGNMENT1COFFEEPOT_SIM533_H__
#define __ASSIGNMENT1COFFEEPOT_SIM533_H__

#include "../../ENCM511_SpecificFiles/ENCM511_include/CoffeePot_SimulatorFunctions2017.h"
#include <stdio.h>

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

//Prototypes for Coffee Pot Assignment 1 Assembly Functions
extern "C" void demonstrateLEDASM(COFFEEPOT_DEVICE *coffeePot);
extern "C" void checkForCoffeePodASM(COFFEEPOT_DEVICE *coffeePot);



#endif /* __ASSIGNMENT1COFFEEPOT_SIM533_H__ */
