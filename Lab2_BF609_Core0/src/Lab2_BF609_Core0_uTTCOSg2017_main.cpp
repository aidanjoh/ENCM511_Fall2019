/*************************************************************************************
* AUTO-GENERATED COMMENT - DO NOT MODIFY 
* Author: aidan 
* Date: Thu 2019/10/24 at 02:31:12 PM 
* File Type: TTCOS Main File
*************************************************************************************/

// This is an example TT_COS main( ) function with threads.
// Use this as a template for your own TT_COS main( ) for the various Threads

#include "Lab2_BF609_Core0_uTTCOSg2017_main.h"

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

//change these names
volatile char ID_frontPanelThread1 = 0;
volatile char ID_frontPanelThread2 = 0;
volatile char ID_frontPanelThread3 = 0;
volatile char ID_frontPanelThread4 = 0;
volatile char ID_frontPanelThread5 = 0;

bool My_Init_LEDInterface_Done = false;
bool My_Init_SwitchInterface_Done = false;
bool My_Init_GPIO_REB_Input_Done = false;
bool My_Init_GPIO_REB_Output_Done = false;
bool My_Init_GPIO_REB_Done = false;


void main(void)
{
	// Make maxNumberThreads at least 5 larger than the 
	//            number of threads you plan to add
	int numBackgroundThreads = 5;
	int numberYourThreads = 8;
	int maxNumberThreads = numBackgroundThreads + numberYourThreads;  

	My_Init_SwitchInterface();  //This function is initiating the switches on the panel
	My_Init_GPIO_REB_InputASM(); //This function is initiating the switches on the board
	My_Init_LEDInterface();  //This function is initiating the LEDS on the panel
	My_Init_GPIO_REB_OutputASM(); //This function is initiating the LEDs on the board

	Custom_uTTCOS_OS_Init(TIC_CONTROL_VALUE);  // Need to update to handle coretimer interrupts

	ID_frontPanelThread1 = uTTCOSg_AddThread(frontPanelThread1, NO_DELAY, 0.5 * ONE_SECOND);
	ID_frontPanelThread2 = uTTCOSg_AddThread(frontPanelThread2, NO_DELAY, 1.2 * ONE_SECOND);
	ID_frontPanelThread3 = uTTCOSg_AddThread(frontPanelThread3, NO_DELAY, 1.0 * ONE_SECOND);
	ID_frontPanelThread4 = uTTCOSg_AddThread(frontPanelThread4, NO_DELAY, 0.01 * ONE_SECOND);
	ID_frontPanelThread5 = uTTCOSg_AddThread(frontPanelThread5, NO_DELAY, 0.01 * ONE_SECOND);

	uTTCOSg_Start_CoreTimer_Scheduler(maxNumberThreads);   //  Start the scheduler timer
					// Execution time of TT_COS_Dispatch( ) and TT_COS_Update( ) improved by specifiying maxNumberTasks

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
	uTTCOSg_DeleteThread(ID_frontPanelThread1);
	uTTCOSg_DeleteThread(ID_frontPanelThread2);    // This stops the thread
	uTTCOSg_DeleteThread(ID_frontPanelThread3);
	uTTCOSg_DeleteThread(ID_frontPanelThread4);
	uTTCOSg_DeleteThread(ID_frontPanelThread5);
}

void My_Init_SwitchInterface(void) //This function is initializing the Switches on the Panel
{
	//printf("Stub for My_Init_SwitchInterface() \n");
	My_Init_SwitchInterface_Done = true;

#ifdef __ADSPBF609__
	Init_GPIO_FrontPanelSwitches();
#endif
}

void My_Init_LEDInterface(void) //This function is initializing the LEDs on the Panel
{
	//printf("Stub for My_Init_LEDInterface() \n");
	My_Init_LEDInterface_Done = true;

	#ifdef __ADSPBF609__
		Init_GPIO_FrontPanelLEDS();
	#endif

}

void My_Init_GPIO_REB_Input(void) //This function is initializing the switches on the Board
{
	//printf("Stub for My_Init_GPIO_REB_Input() \n");
	My_Init_GPIO_REB_Input_Done = true;

	#ifdef __ADSPBF609__
#if 0
		My_Init_GPIO_REB_InputCpp();
#else
		My_Init_GPIO_REB_InputASM();
#endif

	#endif
}

void My_Init_GPIO_REB_Output(void) //This function is initializing the LEDs on the Board
{
	//printf("Stub for My_Init_GPIO_REB_Output");
	My_Init_GPIO_REB_Output_Done = true;

	#ifdef __ADSPBF609__
#if 0
		My_Init_GPIO_REB_OutputCpp();
#else
		My_Init_GPIO_REB_OutputASM();
#endif
	#endif
}
