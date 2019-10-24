/*************************************************************************************
* AUTO-GENERATED COMMENT - DO NOT MODIFY 
* Author: smithmr 
* Date: Mon 2019/10/14 at 08:19:07 AM 
* File Type: TTCOS Main File
*************************************************************************************/

// This is an example TT_COS main( ) function with threads.
// Use this as a template for your own TT_COS main( ) for the various Threads

#include "Example_uTTCOSg2017_main.h"

// TODO -- Update this code to use CORETIMER interrupts to allow slow uTTCOS in BF533 simulator
// TODO Just these values so that 100 TICS tacks about 1 second
#if defined(__ADSPBF609__)
#define  TIC_CONTROL_VALUE ((unsigned long int) 4800000)		// BF609 EMULATOR
#define TICS_PER_SECOND 	100
#define ONE_SECOND 			TICS_PER_SECOND		// If TICS_CONTROL_VALUE Adjusted correctly
#define RUN_ONCE			0
#define NO_DELAY			0
#else
#error "Unknown ADSP or ARM processor"
#endif

void main(void) {
	// Make maxNumberThreads at least 5 larger than the 
	//            number of threads you plan to add
	int numBackgroundThreads = 5;
	int numberYourThreads = 4;
	int maxNumberThreads = numBackgroundThreads + numberYourThreads;  

	Custom_uTTCOS_OS_Init(TIC_CONTROL_VALUE);  // Need to update to handle coretimer interrupts

	// TODO -- Remove this TODO statement and next line when demo is finished and you start your Lab 2
	Set_Up_NOT_START_RemoveMeSoonTasks( );

#warning "You will need to activate the next line to start the uTTCOS Clock scheduler
	uTTCOSg_Start_CoreTimer_Scheduler(maxNumberThreads);   //  Start the scheduler timer
				// Execution time of TT_COS_Dispatch( ) and TT_COS_Update( ) improved by specifiying maxNumberTasks
	while (1) {

		// Wait, in low power mode, for an interrupt
		// The interrupt service routine calls TTCOS_Update( )
		// uTTCOSg_GoToSleep( );                // Need to update to handle coretimer interrupts
		Idle_WaitForInterrupts_ASM( );

		// Run all the threads in the system according
		// to whether their delays have expired
		uTTCOSg_DispatchThreads( );
	}
}

#warning "Once you have demonstrated uTTCOS  -- Comment out the following lines
// Set up uTTCOS path to function that this task needs to interact with
extern volatile char ID_Task_RemoveMeSoon_Print1;
extern volatile char ID_Task_RemoveMeSoon_Print2;
extern volatile char ID_Task_KillerOfPrintStatements_Hunting;
void Set_Up_NOT_START_RemoveMeSoonTasks(void) {
	printf("\n\nSET UP TASKS -- THEY DO NOT START IMMEDIATELY\n\n");
	ID_Task_RemoveMeSoon_Print1 = uTTCOSg_AddThread(Task_RemoveMeSoon_Print1, NO_DELAY, 0.75 * ONE_SECOND);
	ID_Task_RemoveMeSoon_Print2 = uTTCOSg_AddThread(Task_RemoveMeSoon_Print2, NO_DELAY, 2.5 * ONE_SECOND);
	ID_Task_KillerOfPrintStatements_Hunting = uTTCOSg_AddThread(KillerOfPrintStatements_Hunting, 8.5 * ONE_SECOND, RUN_ONCE);
	uTTCOSg_AddThread(TheEnd, 60 * ONE_SECOND, RUN_ONCE);
}

extern volatile char ID_Task_KillerOfPrintStatements;    // Set up uTTCOS path to function that this task needs to interact with
volatile char ID_Task_KillerOfPrintStatements_Hunting;   // Location to store this functions uTTCOS ID
void KillerOfPrintStatements_Hunting(void){
	printf("\nWhat story about an 'UNFRIENDLY GIANT' has the line 'FEE-FI-FO-FUM'?\n");
	printf(" I'm Looking for you -- RemoveMeSoon_Print1\n");
	printf("****  I am tired -- I am setting my big friend after you ***\n\n");
	ID_Task_KillerOfPrintStatements = uTTCOSg_AddThread(KillerOfPrintStatements, 5.0 * ONE_SECOND, RUN_ONCE);
}

extern volatile char ID_Task_RemoveMeSoon_Print1;		// Set up uTTCOS path to function that this task needs to interact with
volatile char ID_Task_KillerOfPrintStatements;			// Location to store this functions uTTCOS ID
void KillerOfPrintStatements(void) {
	printf("\n *** Found you my little precious  ***\n");
	printf("\n The next line is distressing -- READER DISCRETION IS ADVISED\n");
	printf(" HORRIBLE SOUNDS\n\n");

	uTTCOSg_DeleteThread(ID_Task_RemoveMeSoon_Print1);    // This stops the thread
}

extern volatile char ID_Task_RemoveMeSoon_Print2;
void TheEnd(void) {
	printf("\n *******************************\n");
	printf("The world is saved -- PRINT2 can go home and have a beer\n");
	uTTCOSg_DeleteThread(ID_Task_RemoveMeSoon_Print2);    // This stops the thread
}


