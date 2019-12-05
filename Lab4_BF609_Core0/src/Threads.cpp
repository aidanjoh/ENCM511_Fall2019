/*
 * Threads.cpp
 *
 *  Created on: Dec 4, 2019
 *      Author: aidan
 */
#include "Lab4_BF609_Core0_uTTCOSg2017_main.h"

#define SECOND 480000000
#define LLSW8	0x100
#define INSTRUCTIONBIT 0x0400
#define E_BIT_HIGH	0x0100
#define E_BIT_LOW 0x0000
#define CLEARSCREEN 0x01

unsigned long LCDBuffer[1000];
char clr_scrn[] = {CLEAR_SCREEN, '\0'};
int bufferCounter = 0;
int LCDBufferIndex = 0;

volatile char ID_TASK_GPTimerThread;
void GPTimerThread(void)
{
	unsigned long int temperature;
	unsigned long int T2;
	unsigned long int T1;
	char tempBuffer[10];

	T2 = ReadWidth_GP_Timer(3);
	T1 = (ReadPeriod_GP_Timer(3) - T2);
	temperature = 235 - ((400*T1)/T2);

	int index = snprintf(tempBuffer, 10, "%d", temperature);
	char Message[] = " TEMP: ";
	convertStringToLCDMessage(clr_scrn, LCDBuffer, false);
	convertStringToLCDMessage(Message, LCDBuffer, true);
	convertStringToLCDMessage(tempBuffer, LCDBuffer, true);
}

volatile char ID_Task_writingPrelabThread;
void writingPrelabThread(void)
{
  char Message[] = " ENCM 511 RULS ";
  convertStringToLCDMessage(clr_scrn, LCDBuffer, false);
  convertStringToLCDMessage(Message, LCDBuffer, true);
}

volatile char ID_Task_writingInitialsThread;
void writingInitialsThread(void)
{
  char Message[] = " AJ > MP ";
  convertStringToLCDMessage(clr_scrn, LCDBuffer, false);
  convertStringToLCDMessage(Message, LCDBuffer, true);
}

volatile char ID_Task_SPIWriteThread;
void SPIWriteThread(void)
{
  if(REB_SPI_Ready() && (LCDBufferIndex < bufferCounter))
  {
    REB_Write_SPI(LCDBuffer[LCDBufferIndex++]);
  }

  if(LCDBufferIndex == bufferCounter)
  {
    LCDBufferIndex = 0;
    bufferCounter = 0;
  }
}

void initializeLCD(void)
{
	unsigned long int timeWaited = (SECOND*0.01);
	unsigned long int value = 0;

	value = value | LLSW8; //setting logic lab switch 8 to high
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value | 0x30;
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value & 0xfeff;
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value | LLSW8;
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value & 0xfeff;
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value | LLSW8;
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value | 0x003c;
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value & 0xfeff;
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value | LLSW8;
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value & 0xff0f;
	value = value | 0x000f;
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value & 0xfeff;
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value | LLSW8;
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value & 0xff00;
	value = value | 0x0001;
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value & 0xfeff;
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value | LLSW8;
	REB_Write_SPI(value);
	waitABit(timeWaited);
}

void waitABit(unsigned long int timeValue)
{
	while(timeValue)
	{
		timeValue--;
	}
}

unsigned short convertStringToLCDMessage(char* Data, unsigned long* TargetBuffer, bool isData){
  int counter = 0;

  while(Data[counter] != '\0'){
    if(isData){
      TargetBuffer[bufferCounter++] = E_BIT_HIGH | DATA | Data[counter];
      TargetBuffer[bufferCounter++] = E_BIT_LOW | DATA | Data[counter];
      TargetBuffer[bufferCounter++] = E_BIT_HIGH | DATA | Data[counter];
    }
    else{
      TargetBuffer[bufferCounter++] = E_BIT_HIGH | INSTRUCTION | Data[counter];
      TargetBuffer[bufferCounter++] = E_BIT_LOW | INSTRUCTION | Data[counter];
      TargetBuffer[bufferCounter++] = E_BIT_HIGH | INSTRUCTION | Data[counter];
    }
    counter++;
  }
  return counter;
}

