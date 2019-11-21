/*************************************************************************************
*   AUTOMATICALLY GENERATED COMMENT -- DO NOT MODIFY
* Author: aidan
* Date: Thu 2019/11/21 at 10:55:00 AM
* File Type: EUNIT Main File
*************************************************************************************/

#include <EmbeddedUnit2017/EmbeddedUnit2017.h>
#include "Lab2EUNITTesting.h"
void UpdateEunitGui(void);
extern volatile int useLongFileFormat;

extern void AutomatedTestLevelControl(void);

void RestartEunitGui(void);
void UpdateEunitGui(void);

int main(void)
{
	int failureCount;

	RestartEunitGui( ); 
	UpdateEunitGui();
	
	UnitTest::ProcessorSpecificStartup();

	AutomatedTestLevelControl();

	UnitTest::Test::GetTestList().ReverseListDirection();

	bool showFail = true;	bool showXFail = true;
	bool showSuccesses = true;

// TODO You can adjust UnitTest::RunAllTests( ) parameters to show only failures -- Wed 2018/09/26 at 08:14:10 PM
// TODO          by setting bool showSuccesses = false;;
	failureCount = UnitTest::RunAllTests(showFail, showXFail, showSuccesses);
	
	UpdateEunitGui();
	return failureCount;
}
