/*************************************************************************************
* AUTO-GENERATED COMMENT - DO NOT MODIFY 
* Author: aidan 
* Date: Tue 2019/12/03 at 04:44:36 PM 
* File Type: TTCOS Main File
*************************************************************************************/

// This is an example TT_COS main( ) function with threads.
// Use this as a template for your own TT_COS main( ) for the various Threads

#include "Lab4_BF609_Core0_uTTCOSg2017_main.h"
#include "adi_initialize.h"

#if defined(__ADSPBF609__)
#define  TIC_CONTROL_VALUE ((unsigned long int) 4800000)		// BF609 EMULATOR
#define TICS_PER_SECOND 	100
#define ONE_SECOND 			TICS_PER_SECOND		// If TICS_CONTROL_VALUE Adjusted correctly
#define RUN_ONCE			0
#define NO_DELAY			0
#else
#error "Unknown ADSP or ARM processor"
#endif


extern volatile char ID_writingPrelabMessage = 0;
extern volatile char ID_writingTemperatureMessage = 0;
extern volatile char ID_writingInitials = 0;
extern volatile char ID_temperature = 0;

char Buffer[1000];

void main(void)
{
	adi_initComponents();

	Init_GP_Timer(3);
	Start_GP_Timer(3);
	Init_REB_SPI();
	Start_REB_SPI();
	initializeLCD();

	// Make maxNumberThreads at least 5 larger than the 
	//            number of threads you plan to add
	int numBackgroundThreads = 5;
	int numberYourThreads = 4;
	int maxNumberThreads = numBackgroundThreads + numberYourThreads;  

	Custom_uTTCOS_OS_Init(TIC_CONTROL_VALUE);  // Need to update to handle coretimer interrupts

	//Code to run the Lab 4 threads
	ID_writingPrelabMessage = uTTCOSg_AddThread(writingPrelabMessage, NO_DELAY, 7*ONE_SECOND);
	ID_writingTemperatureMessage = uTTCOSg_AddThread(writingTemperatureMessage, NO_DELAY, 7* ONE_SECOND);
	ID_writingInitials = uTTCOSg_AddThread(writingInitials, NO_DELAY, 7*ONE_SECOND);
	ID_temperature = uTTCOSg_AddThread(writingTemperature, NO_DELAY, ONE_SECOND);

	uTTCOSg_Start_CoreTimer_Scheduler(maxNumberThreads);   //  Start the scheduler timer
	// Execution time of TT_COS_Dispatch( ) and TT_COS_Update( ) improved by specifiying maxNumberTasks

	while (1)
	{
		// Wait, in low power mode, for an interrupt
		// The interrupt service routine calls TTCOS_Update( )
		// uTTCOSg_GoToSleep( );                // Need to update to handle coretimer interrupts
		Idle_WaitForInterrupts_ASM( );

		// Run all the threads in the system according
		// to whether their delays have expired
		uTTCOSg_DispatchThreads( );
	}
}

#define SECOND 480000000
#define LLSW8	0x100
#define INSTRUCTIONBIT 0x0400
#define E_BIT_HIGH	0x0100
#define E_BIT_LOW 0x0000
#define CLEARSCREEN 0x01

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

void writingPrelabMessage(void)
{
		unsigned long int timeWaited = (SECOND*0.01);
		unsigned long int value = 0;

		value = value & 0xff00; //Clearing the bits
		value = value | 0x0400; //setting logic lab switch 10 to high

		value = value | 0x20; //This is ascii space
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

		value = value & 0xff00;
		value = value | 0x35; //This is 5
		REB_Write_SPI(value);
		waitABit(timeWaited);

		value = value & 0xfeff;
		REB_Write_SPI(value);
		waitABit(timeWaited);

		value = value | LLSW8;
		REB_Write_SPI(value);
		waitABit(timeWaited);

		value = value & 0xff00;
		value = value | 0x31; //This is 1
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

		value = value & 0xff00;
		value = value | 0x20; //This is ascii space
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

		value = value & 0xff00;
		value = value | 0x52; //This is R
		REB_Write_SPI(value);
		waitABit(timeWaited);

		value = value & 0xfeff;
		REB_Write_SPI(value);
		waitABit(timeWaited);

		value = value | LLSW8;
		REB_Write_SPI(value);
		waitABit(timeWaited);

		value = value & 0xff00;
		value = value | 0x55; //This is U
		REB_Write_SPI(value);
		waitABit(timeWaited);

		value = value & 0xfeff;
		REB_Write_SPI(value);
		waitABit(timeWaited);

		value = value | LLSW8;
		REB_Write_SPI(value);
		waitABit(timeWaited);

		value = value & 0xff00;
		value = value | 0x4c; //This is L
		REB_Write_SPI(value);
		waitABit(timeWaited);

		value = value & 0xfeff;
		REB_Write_SPI(value);
		waitABit(timeWaited);

		value = value | LLSW8;
		REB_Write_SPI(value);
		waitABit(timeWaited);

		value = value & 0xff00;
		value = value | 0x53; //This is S
		REB_Write_SPI(value);
		waitABit(timeWaited);

		value = value & 0xfeff;
		REB_Write_SPI(value);
		waitABit(timeWaited);

		value = value | LLSW8;
		REB_Write_SPI(value);
		waitABit(timeWaited);

		value = value & 0xff00;
		value = value | 0x20; //This is ascii space
		REB_Write_SPI(value);
		waitABit(timeWaited);

		value = value & 0xfeff;
		REB_Write_SPI(value);
		waitABit(timeWaited);

		value = value | LLSW8;
		REB_Write_SPI(value);
		waitABit(timeWaited);

		clearScreen();
}

void temperature(void)
{

}

void writingInitials(void)
{
		unsigned long int timeWaited = (SECOND*0.01);
		unsigned long int value = 0;

		value = value & 0xff00; //Clearing the bits
		value = value | 0x0400; //setting logic lab switch 10 to high

		value = value | 0x20; //This is ascii space
		REB_Write_SPI(value);
		waitABit(timeWaited);

		value = value & 0xfeff;
		REB_Write_SPI(value);
		waitABit(timeWaited);

		value = value | LLSW8;
		REB_Write_SPI(value);
		waitABit(timeWaited);

		value = value | 0x41; //This is A
		REB_Write_SPI(value);
		waitABit(timeWaited);

		value = value & 0xfeff;
		REB_Write_SPI(value);
		waitABit(timeWaited);

		value = value | LLSW8;
		REB_Write_SPI(value);
		waitABit(timeWaited);

		value = value | 0x4A; //This is J
		REB_Write_SPI(value);
		waitABit(timeWaited);

		value = value & 0xfeff;
		REB_Write_SPI(value);
		waitABit(timeWaited);

		value = value | LLSW8;
		REB_Write_SPI(value);
		waitABit(timeWaited);

		value = value | 0x20; //This is ascii space
		REB_Write_SPI(value);
		waitABit(timeWaited);

		value = value & 0xfeff;
		REB_Write_SPI(value);
		waitABit(timeWaited);

		value = value | LLSW8;
		REB_Write_SPI(value);
		waitABit(timeWaited);

		value = value | 0x4D; //This is M
		REB_Write_SPI(value);
		waitABit(timeWaited);

		value = value & 0xfeff;
		REB_Write_SPI(value);
		waitABit(timeWaited);

		value = value | LLSW8;
		REB_Write_SPI(value);
		waitABit(timeWaited);

		value = value | 0x50; //This is P
		REB_Write_SPI(value);
		waitABit(timeWaited);

		value = value & 0xfeff;
		REB_Write_SPI(value);
		waitABit(timeWaited);

		value = value | LLSW8;
		REB_Write_SPI(value);
		waitABit(timeWaited);

		clearScreen();
}

void writingTemperatureMessage(void)
{
		unsigned long int timeWaited = (SECOND*0.01);
		unsigned long int value = 0;

		value = value & 0xff00; //Clearing the bits
		value = value | 0x0400; //setting logic lab switch 10 to high

		value = value | 0x20; //This is ascii space
		REB_Write_SPI(value);
		waitABit(timeWaited);

		value = value & 0xfeff;
		REB_Write_SPI(value);
		waitABit(timeWaited);

		value = value | LLSW8;
		REB_Write_SPI(value);
		waitABit(timeWaited);

		value = value | 0x54; //This is T
		REB_Write_SPI(value);
		waitABit(timeWaited);

		value = value & 0xfeff;
		REB_Write_SPI(value);
		waitABit(timeWaited);

		value = value | LLSW8;
		REB_Write_SPI(value);
		waitABit(timeWaited);

		value = value | 0x45; //This is E
		REB_Write_SPI(value);
		waitABit(timeWaited);

		value = value & 0xfeff;
		REB_Write_SPI(value);
		waitABit(timeWaited);

		value = value | LLSW8;
		REB_Write_SPI(value);
		waitABit(timeWaited);

		value = value | 0x4D; //This is M
		REB_Write_SPI(value);
		waitABit(timeWaited);

		value = value & 0xfeff;
		REB_Write_SPI(value);
		waitABit(timeWaited);

		value = value | LLSW8;
		REB_Write_SPI(value);
		waitABit(timeWaited);

		value = value | 0x50; //This is P
		REB_Write_SPI(value);
		waitABit(timeWaited);

		value = value & 0xfeff;
		REB_Write_SPI(value);
		waitABit(timeWaited);

		value = value | LLSW8;
		REB_Write_SPI(value);
		waitABit(timeWaited);

		value = value | 0x3A; //This is :
		REB_Write_SPI(value);
		waitABit(timeWaited);

		value = value & 0xfeff;
		REB_Write_SPI(value);
		waitABit(timeWaited);

		value = value | LLSW8;
		REB_Write_SPI(value);
		waitABit(timeWaited);

		value = value | 0x20; //This is ascii space
		REB_Write_SPI(value);
		waitABit(timeWaited);

		value = value & 0xfeff;
		REB_Write_SPI(value);
		waitABit(timeWaited);

		value = value | LLSW8;
		REB_Write_SPI(value);
		waitABit(timeWaited);

		clearScreen();
}


void clearScreen(void)
{
	unsigned long int value = 0;
	unsigned long int timeWaited = (SECOND*0.01);

	value = value | E_BIT_HIGH;
	value = value & (~INSTRUCTIONBIT);
	value = value | CLEARSCREEN;
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value & (~E_BIT_HIGH);
	REB_Write_SPI(value);
	waitABit(timeWaited);

	value = value | E_BIT_HIGH;
	REB_Write_SPI(value);
	waitABit(timeWaited);
}



