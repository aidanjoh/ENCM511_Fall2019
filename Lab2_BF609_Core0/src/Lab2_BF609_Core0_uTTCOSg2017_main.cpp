/*************************************************************************************
* AUTO-GENERATED COMMENT - DO NOT MODIFY 
* Author: aidan 
* Date: Thu 2019/10/24 at 02:31:12 PM 
* File Type: TTCOS Main File
*************************************************************************************/
#include "Lab2_BF609_Core0_uTTCOSg2017_main.h"

//change these names
extern volatile char ID_frontPanelThread1 = 0;
extern volatile char ID_frontPanelThread2 = 0;
extern volatile char ID_frontPanelThread3 = 0;
extern volatile char ID_frontPanelThread4 = 0;
extern volatile char ID_frontPanelThread5 = 0;
extern volatile char ID_REBThread1 = 0;
extern volatile char ID_REBThread2 = 0;
extern volatile char ID_REBThread3 = 0;

bool My_Init_LEDInterface_Done = false;
bool My_Init_SwitchInterface_Done = false;
bool My_Init_GPIO_REB_Input_Done = false;
bool My_Init_GPIO_REB_Output_Done = false;
bool My_Init_GPIO_REB_Done = false;


void main(void)
{
	int numBackgroundThreads = 5; // Make maxNumberThreads at least 5 larger than the number of threads you plan to add
	int numberYourThreads = 11; //We have 8 threads (5 front panel threads and 3 REB threads) + 3 for Lab 4
	int maxNumberThreads = numBackgroundThreads + numberYourThreads;  

	My_Init_SwitchInterface();  //This function is initiating the switches on the panel
	My_Init_GPIO_REB_InputASM(); //This function is initiating the switches on the board
	My_Init_LEDInterface();  //This function is initiating the LEDS on the panel
	My_Init_GPIO_REB_OutputASM(); //This function is initiating the LEDs on the board

	Custom_uTTCOS_OS_Init(TIC_CONTROL_VALUE);  // Need to update to handle core-timer interrupts

	//Code to run the FP threads
	ID_frontPanelThread1 = uTTCOSg_AddThread(frontPanelThread1, NO_DELAY, 0.25 * ONE_SECOND);
	ID_frontPanelThread2 = uTTCOSg_AddThread(frontPanelThread2, NO_DELAY, 0.4 * ONE_SECOND);
	ID_frontPanelThread3 = uTTCOSg_AddThread(frontPanelThread3, NO_DELAY, 0.5 * ONE_SECOND);
	ID_frontPanelThread4 = uTTCOSg_AddThread(frontPanelThread4, NO_DELAY, 0.01 * ONE_SECOND);
	ID_frontPanelThread5 = uTTCOSg_AddThread(frontPanelThread5, NO_DELAY, 0.01 * ONE_SECOND);


	//Code to run the REB threads
	ID_REBThread1 = uTTCOSg_AddThread(REBThread1, NO_DELAY, 0.25 * ONE_SECOND);
	ID_REBThread2 = uTTCOSg_AddThread(REBThread2, NO_DELAY, 0.01 * ONE_SECOND);
	ID_REBThread3 = uTTCOSg_AddThread(REBThread3, NO_DELAY, 0.25 * ONE_SECOND);

	uTTCOSg_Start_CoreTimer_Scheduler(maxNumberThreads);   //  Start the scheduler timer
					// Execution time of TT_COS_Dispatch( ) and TT_COS_Update( ) improved by specifying maxNumberTasks

	while (1)
	{
		// Wait, in low power mode, for an interrupt
		// The interrupt service routine calls TTCOS_Update( )
		// uTTCOSg_GoToSleep( );                // Need to update to handle coretimer interrupts
		Idle_WaitForInterrupts_ASM();

		// Run all the threads in the system according
		// to whether their delays have expired
		uTTCOSg_DispatchThreads();
	}
}
