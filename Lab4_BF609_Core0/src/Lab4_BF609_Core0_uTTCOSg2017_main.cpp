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


extern volatile char ID_SPIWrite = 0;
extern volatile char ID_GPTimer = 0;
extern volatile char ID_writingInitials = 0;
extern volatile char ID_writingPrelab = 0;

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
	ID_SPIWrite = uTTCOSg_AddThread(SPIWriteThread, NO_DELAY, 0.05*ONE_SECOND);
	ID_GPTimer = uTTCOSg_AddThread(GPTimerThread, NO_DELAY, 2*ONE_SECOND);
	ID_writingInitials = uTTCOSg_AddThread(writingInitialsThread, NO_DELAY, 5*ONE_SECOND);
	ID_writingPrelab = uTTCOSg_AddThread(writingPrelabThread, NO_DELAY, 7*ONE_SECOND);

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
