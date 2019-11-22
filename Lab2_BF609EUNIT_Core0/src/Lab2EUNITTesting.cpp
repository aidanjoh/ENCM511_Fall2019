/*************************************************************************************
*   AUTOMATICALLY GENERATED COMMENT -- DO NOT MODIFY
* Author: aidan
* Date: Thu 2019/11/21 at 10:55:00 AM
* File Type: EUNIT Test File
*************************************************************************************/

#define EMBEDDEDUNIT_LITE
#include <EmbeddedUnit2017/EmbeddedUnit2017.h>
#include "Lab2EUNITTesting.h"


TEST_CONTROL(Lab2EUNITTesting_cpp);

#if 1
void UpdateEunitGui(void);
TEST(Lab2EUNITTesting_cpp_GUIUpdate) {
	UpdateEunitGui();  // Conditionally compile this line (use #if 0) to stop an GUI update based on last completed test
}
#endif


unsigned short int TestBitwiseAND(unsigned short int bitPattern, unsigned short int bitMask);
unsigned short int TestBitwiseOR(unsigned short int bitPattern, unsigned short int bitMask);

#if 0
TEST(Thread1to3_MoreComplexTest)
{ 
	#warning 'Dummy test has been inserted -- replace with your own -- Thu 2019/11/21 at 10:55:00 AM '
	// TODO -- 'Dummy test has been inserted  -- replace with your own -- Thu 2019/11/21 at 10:55:00 AM '
	printf("Dummy test has been inserted -- replace with your own -- Thu 2019/11/21 at 10:55:00 AM \n");
	
	unsigned long int value  			= 0x01FF01FF;
	unsigned long int ORmask 			= 0x0F000F0F;
	unsigned long int expectedORResult 	= 0x0100010F;
	unsigned long int resultOR  = TestBitwiseOR(value, ORmask);
	CHECK(expectedORResult == resultOR);
	CHECK_EQUAL(expectedORResult, resultOR);
	
	#error("You insert the 'wrong' test for TestBitwiseAND";
}

unsigned short int TestBitwiseAND(unsigned short int bitPattern, unsigned short int bitMask) {
	return bitPattern && bitMask;
}

unsigned short int TestBitwiseOR(unsigned short int bitPattern, unsigned short int bitMask) {
	return bitPattern || bitMask;
}

TEST(Thread1to3_Successes)
{ 
	#warning 'Dummy test has been inserted -- replace with your own -- Thu 2019/11/21 at 10:55:00 AM '
	// TODO -- 'Dummy test has been inserted  -- replace with your own -- Thu 2019/11/21 at 10:55:00 AM '
	printf("Dummy test has been inserted -- replace with your own -- Thu 2019/11/21 at 10:55:00 AM \n");
	
	CHECK(false == false);
	CHECK_EQUAL(false, false);
	
	XF_CHECK(false == true);    // Expected failure occurs
	XF_CHECK_EQUAL(false, true); // Expected failure occurs
	XF_CHECK(false == false);    // Expected failure does not occur
	XF_CHECK_EQUAL(false, false); // Expected failure does not occur
	
	#error("You insert the 'wrong' test for TestBitwiseAND";
}

#endif

bool My_Init_LEDInterface_Done = false;
bool My_Init_SwitchInterface_Done = false;
bool My_Init_GPIO_REB_Input_Done = false;
bool My_Init_GPIO_REB_Output_Done = false;
bool My_Init_GPIO_REB_Done = false;

TEST(Thread1to3)
{ 
	printf("EUNIT Test for Threads 1 to 3 \n");

	My_Init_SwitchInterface();  //This function is initiating the switches on the panel
	My_Init_LEDInterface();  //This function is initiating the LEDS on the panel

	unsigned char expectedValue = 0x00;
	unsigned char value = 0;

	//Time 0.25 seconds
	//TODO thread 1 check
	//should be off

	frontPanelThread1();
	value = myReadFrontPanelLEDs();
	value = value & LED8VALUE;

	CHECK_EQUAL(expectedValue, value);

	//Time 0.4 seconds
	//TODO thread 2 check
	//should be off

	frontPanelThread2();
	value = myReadFrontPanelLEDs();
	value = value & LED7VALUE;

	expectedValue = 0x00;
	CHECK_EQUAL(expectedValue, value);

	//Time 0.5 seconds
	//TODO thread 1 and 3 check
	//thread 1 should be on and thread as a 0
	frontPanelThread1();
	frontPanelThread3();
	value = myReadFrontPanelLEDs();
	value = value & LED8AND1AND2VALUE;

	expectedValue = 0x80;
	CHECK_EQUAL(expectedValue, value);

	//Time 0.75 seconds
	//TODO thread 1 check
	//Thread 1 should be off
	frontPanelThread1();
	value = myReadFrontPanelLEDs();
	value = value & LED8VALUE;

	expectedValue = 0x00;
	CHECK_EQUAL(expectedValue, value);

	//Time 0.8 seconds
	//TODO thread 2 check
	//Thread 2 should be on
	frontPanelThread2();
	value = myReadFrontPanelLEDs();
	value = value & LED7VALUE;

	expectedValue = 0x40;
	CHECK_EQUAL(expectedValue, value);

	//Time 1 second
	//TODO check thread 1 and 3
	//Thread 1 should be on and thread 3 should display a 1 with thread 2 still on
	frontPanelThread1();
	frontPanelThread3();
	value = myReadFrontPanelLEDs();
	value = value & LED871AND2VALUE;

	expectedValue = 0xc1;
	CHECK_EQUAL(expectedValue, value);

	//Time 1.2 seconds
	//TODO check thread 2
	//Thread 2 should be on, with thread 1 on and thread 3 displaying a 1
	frontPanelThread2();
	value = myReadFrontPanelLEDs();
	value = value & LED871AND2VALUE;

	expectedValue = 0xc1;
	CHECK_EQUAL(expectedValue, value);

	//Time 1.25 seconds
	//TODO check thread 1
	//Thread 1 should be off, with thread 2 on and thread 3 displaying a 1
	frontPanelThread1();
	value = myReadFrontPanelLEDs();
	value = value & LED871AND2VALUE;

	expectedValue = 0x41;
	CHECK_EQUAL(expectedValue, value);

	//Time 1.50 seconds
	//TODO check thread 1 and 3
	//Thread 1 should be on and thread 3 should display a 2, with thread 2 on
	frontPanelThread1();
	frontPanelThread3();
	value = myReadFrontPanelLEDs();
	value = value & LED871AND2VALUE;

	expectedValue = 0xc2;
	CHECK_EQUAL(expectedValue, value);

	//Time 1.6 seconds
	//TODO check thread 2
	//Thread 2 should be off, with thread 1 on and thread 3 displaying a 2
	frontPanelThread2();
	value = myReadFrontPanelLEDs();
	value = value & LED871AND2VALUE;

	expectedValue = 0x82;
	CHECK_EQUAL(expectedValue, value);

	//Time 1.75 seconds
	//TODO check thread 1
	//Thread 1 should be off, with thread 2 off and thread 3 displaying a 2
	frontPanelThread1();
	value = myReadFrontPanelLEDs();
	value = value & LED871AND2VALUE;

	expectedValue = 0x02;
	CHECK_EQUAL(expectedValue, value);

	//Time 2 seconds
	//TODO check thread 1, 2 and 3
	//Thread 1 should be on, thread 2 should be on and thread 3 should display a 3
	frontPanelThread1();
	frontPanelThread2();
	frontPanelThread3();
	value = myReadFrontPanelLEDs();
	value = value & LED871AND2VALUE;

	expectedValue = 0xc3;
	CHECK_EQUAL(expectedValue, value);

}




TEST_FILE_RUN_NOTIFICATION(Lab2EUNITTesting_cpp);



