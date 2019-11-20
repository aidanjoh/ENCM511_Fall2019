/*************************************************************************************
*   AUTOMATICALLY GENERATED COMMENT -- DO NOT MODIFY
* Author: aidan
* Date: Wed 2019/10/30 at 10:20:29 PM
* File Type: EUNIT Test File
*************************************************************************************/

#define EMBEDDEDUNIT_LITE
#include <EmbeddedUnit2017/EmbeddedUnit2017.h>
//#include "HelloWorld_cpp.h"


TEST_CONTROL(HelloWorld_cpp);

#if 1
void UpdateEunitGui(void);
TEST(HelloWorld_cpp_GUIUpdate) {
	UpdateEunitGui();  // Conditionally compile this line (use #if 0) to stop an GUI update based on last completed test
}
#endif


unsigned short int TestBitwiseAND(unsigned short int bitPattern, unsigned short int bitMask);
unsigned short int TestBitwiseOR(unsigned short int bitPattern, unsigned short int bitMask);

#if 0
TEST(Test1_MoreComplexTest)
{ 
	#warning 'Dummy test has been inserted -- replace with your own -- Wed 2019/10/30 at 10:20:29 PM '
	// TODO -- 'Dummy test has been inserted  -- replace with your own -- Wed 2019/10/30 at 10:20:29 PM '
	printf("Dummy test has been inserted -- replace with your own -- Wed 2019/10/30 at 10:20:29 PM \n");
	
	unsigned long int value  			= 0x01FF01FF;
	unsigned long int ORmask 			= 0x0F000F0F;
	unsigned long int expectedORResult 	= 0x0100010F;
	unsigned long int resultOR  = TestBitwiseOR(value, ORmask);
	CHECK(expectedORResult == resultOR);
	CHECK_EQUAL(expectedORResult, resultOR);
	
	//#error 'You insert the 'wrong' test for TestBitwiseAND';
}

unsigned short int TestBitwiseAND(unsigned short int bitPattern, unsigned short int bitMask) {
	return bitPattern && bitMask;
}

unsigned short int TestBitwiseOR(unsigned short int bitPattern, unsigned short int bitMask) {
	return bitPattern || bitMask;
}

TEST(Test1_Successes)
{ 
	#warning 'Dummy test has been inserted -- replace with your own -- Wed 2019/10/30 at 10:20:29 PM '
	// TODO -- 'Dummy test has been inserted  -- replace with your own -- Wed 2019/10/30 at 10:20:29 PM '
	printf("Dummy test has been inserted -- replace with your own -- Wed 2019/10/30 at 10:20:29 PM \n");
	
	CHECK(false == false);
	CHECK_EQUAL(false, false);
	
	XF_CHECK(false == true);    // Expected failure occurs
	XF_CHECK_EQUAL(false, true); // Expected failure occurs
	XF_CHECK(false == false);    // Expected failure does not occur
	XF_CHECK_EQUAL(false, false); // Expected failure does not occur
	
	#error("You insert the 'wrong' test for TestBitwiseAND");
}

#endif

TEST(Test1)
{ 
	CHECK(1 == 1);
}




TEST_FILE_RUN_NOTIFICATION(HelloWorld_cpp);



