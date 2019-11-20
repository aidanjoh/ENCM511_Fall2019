/*
 * CoffeePotSimulatorFunctions2016.h
 *
 *  Created on: Sep 6, 2016
 *  Modified 10 October 2019
 *      Author: smithmr
 */

#ifndef COFFEEPOT_SIMULATORFUNCTIONS2017_H_
#define COFFEEPOT_SIMULATORFUNCTIONS2017_H_

#include "CoffeePot_SimulatorStructures2017.h"

enum WHICHDISPLAY {USE_TEXT_GUI = 1, USE_GRAPHICS_GUI = 2,  USE_TEXT_AND_GRAPHICS_GUIS = 3, USE_SPI_GUI = 4};  // Make all display modes available simultaneously
enum COFFEEPOT_ID {COFFEEPOT1 = 1, COFFEEPOT2, COFFEEPOT3, COFFEEPOT4};

void Init_CoffeePotSimulation(int numCoffeePots, enum WHICHDISPLAY whichDisplay);

void FastForward_OneSimulationTIC(COFFEEPOT_DEVICE *baseAddress);
#define FastForward_OneSimulationTic(A) FastForward_OneSimulationTIC(A)

COFFEEPOT_DEVICE *Add_CoffeePotToSystem_PlugAndPlay(enum COFFEEPOT_ID COFFEEPOT, char coffeePotName[]);

unsigned short int ReadControlRegister_CPP(COFFEEPOT_DEVICE *baseAddress);
unsigned short int CurrentWaterLevel_CPP(COFFEEPOT_DEVICE *baseAddress);
unsigned short int CurrentTemperature_CPP(COFFEEPOT_DEVICE *baseAddress);
void Remove_CoffeePotFromSystem(COFFEEPOT_DEVICE *baseAddress);
void ShowDeviceRegisterValues(COFFEEPOT_DEVICE *baseAddress);
unsigned short int WriteControlRegister_CPP(COFFEEPOT_DEVICE *baseAddress, unsigned short int newControlRegisterValue);

void NetworkTimingFudge_USE_CCES_GUI_Delay(void);

#endif /* COFFEEPOT_SIMULATORFUNCTIONS2016_H_ */
