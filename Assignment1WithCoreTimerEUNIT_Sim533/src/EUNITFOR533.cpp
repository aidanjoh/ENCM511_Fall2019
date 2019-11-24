/*************************************************************************************
*   AUTOMATICALLY GENERATED COMMENT -- DO NOT MODIFY
* Author: aidan
* Date: Sun 2019/11/24 at 01:22:27 PM
* File Type: EUNIT Test File
*************************************************************************************/

#define EMBEDDEDUNIT_LITE
#include <EmbeddedUnit2017/EmbeddedUnit2017.h>
#include "EUNITFOR533.h"


TEST_CONTROL(EUNITFOR533_cpp);

#if 1
void UpdateEunitGui(void);
TEST(EUNITFOR533_cpp_GUIUpdate) {
	UpdateEunitGui();  // Conditionally compile this line (use #if 0) to stop an GUI update based on last completed test
}
#endif


unsigned short int TestBitwiseAND(unsigned short int bitPattern, unsigned short int bitMask);
unsigned short int TestBitwiseOR(unsigned short int bitPattern, unsigned short int bitMask);

#if 0
TEST(TestingTheFourCoreTimerFunctions_MoreComplexTest)
{ 
	#warning 'Dummy test has been inserted -- replace with your own -- Sun 2019/11/24 at 01:22:27 PM '
	// TODO -- 'Dummy test has been inserted  -- replace with your own -- Sun 2019/11/24 at 01:22:27 PM '
	printf("Dummy test has been inserted -- replace with your own -- Sun 2019/11/24 at 01:22:27 PM \n");
	
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

TEST(TestingTheFourCoreTimerFunctions_Successes)
{ 
	#warning 'Dummy test has been inserted -- replace with your own -- Sun 2019/11/24 at 01:22:27 PM '
	// TODO -- 'Dummy test has been inserted  -- replace with your own -- Sun 2019/11/24 at 01:22:27 PM '
	printf("Dummy test has been inserted -- replace with your own -- Sun 2019/11/24 at 01:22:27 PM \n");
	
	CHECK(false == false);
	CHECK_EQUAL(false, false);
	
	XF_CHECK(false == true);    // Expected failure occurs
	XF_CHECK_EQUAL(false, true); // Expected failure occurs
	XF_CHECK(false == false);    // Expected failure does not occur
	XF_CHECK_EQUAL(false, false); // Expected failure does not occur
	
	#error("You insert the 'wrong' test for TestBitwiseAND";
}

#endif

TEST(TestingTheFourCoreTimerFunctions)
{ 
	//Checking if the core timer was properly initialized
	myInit_CoreTimer(PERIOD, COUNT);

	unsigned long int coreTimerControlRegister = CORETIMEPOWERBIT;
	unsigned long int coreTimerPeriodRegister = PERIOD;
	unsigned long int coreTimerCountRegister = COUNT;
	unsigned long int coreTimerScaleRegister = 0x0;

	CHECK_EQUAL(coreTimerControlRegister, *pTCNTL);
	CHECK_EQUAL(coreTimerPeriodRegister, *pTPERIOD);
	CHECK_EQUAL(coreTimerCountRegister, *pTCOUNT);
	CHECK_EQUAL(coreTimerScaleRegister, *pTSCALE);

	//Checking if the core timer was enabled properly
	myControl_CoreTimer((TCNTLTMRENBIT)); //Enabling the Core Timer
	coreTimerControlRegister = (TCNTLBITS3AND1TO0);

	CHECK_EQUAL(coreTimerControlRegister, *pTCNTL);

	//Checking if the core timer went off after the appriopate count
	myTimedWaitOnCoreTimer();
	coreTimerControlRegister = (TCNTLBITS3AND1TO0);

	CHECK_EQUAL(coreTimerControlRegister, *pTCNTL);

	//Checking if the Core timer is complete
	bool isCoreTimerComplete = false;
	isCoreTimerComplete = myCompleted_CoreTimer();

	CHECK_EQUAL(true, isCoreTimerComplete);

	unsigned long int readCyclesValue;
	unsigned long int differenceInCyclesValue;
	unsigned long int prevReadCyclesValue;
	unsigned long int cyclesArray[10];

	readCyclesValue = ReadProcessorCyclesASM();
	cyclesArray[0] = readCyclesValue;
	prevReadCyclesValue = readCyclesValue;

	myControl_CoreTimer(TCNTLTAUTORLDBIT);

	for(int i = 1; i < 10; i++)
	{
		myTimedWaitOnCoreTimer();
		readCyclesValue = ReadProcessorCyclesASM();
		differenceInCyclesValue = readCyclesValue - prevReadCyclesValue;
		cyclesArray[i] = differenceInCyclesValue;
		prevReadCyclesValue = readCyclesValue;
		CHECK_EQUAL(cyclesArray[i-1], cyclesArray[i]);
		isCoreTimerComplete = myCompleted_CoreTimer();
	}

}

void myInit_CoreTimer(unsigned long int period, unsigned long int count)
{

	#if NOTSTUBS
		*pTCNTL = CORETIMEPOWERBIT;
		*pTPERIOD = period;
		*pTCOUNT = count;
		*pTSCALE = 0x00000000;
	#else
			printf("Stub for myInit_CoreTimer");
	#endif

}

void myControl_CoreTimer(unsigned short int cntrl_value)
{
	#if NOTSTUBS
		*pTCNTL = (*pTCNTL | cntrl_value);
	#else
		printf("Stub for myControl_CoreTimer");
	#endif
}

bool myCompleted_CoreTimer(void)
{
	#if NOTSTUBS
		bool returnValue = false;
		unsigned long int coreTimerControlValue = *pTCNTL;

		if((coreTimerControlValue & TCNTLBITS3AND1TO0) == TCNTLBITS3AND1TO0)
		{
			*pTCNTL = *pTCNTL & (~TCNTLDONEBIT);
			returnValue = true;
		}

		return returnValue;
	#else
		printf("Stub for myCompleted_CoreTimer");
	#endif
}

void myTimedWaitOnCoreTimer(void)
{
	#if NOTSTUBS
		bool coreTimerInitialized = false;

		while(!coreTimerInitialized)
		{
			unsigned long int stickyBitTCNTL = (*pTCNTL & TCNTLDONEBIT);
			if(TCNTLDONEBIT == stickyBitTCNTL)
			{
				coreTimerInitialized = true;
			}
		}

		return;
	#else
		printf("Stub for myTimedWaitOnCoreTimer");
	#endif
}



TEST_FILE_RUN_NOTIFICATION(EUNITFOR533_cpp);



