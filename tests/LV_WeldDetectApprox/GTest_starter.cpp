/**
* \file    LV_WeldDetectApprox/GTest_starter.cpp
* \brief	Starter for google test API
* \author  PB
* \date    2014/10/24
*/

#include <windows.h>
#include "gtest/gtest.h"

int main(int argc, char* argv[])
{
	int ret = 0;
	//	HANDLE hLogFile;
	time_t seconds;
	time ( &seconds );
	//	hLogFile = CreateFile("C_WeldLineDetect.mylog", FILE_APPEND_DATA,
	//	FILE_SHARE_WRITE, NULL, CREATE_ALWAYS,
	//	FILE_ATTRIBUTE_NORMAL, NULL);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	//	_CrtSetReportFile(_CRT_WARN, hLogFile);
	_RPT1(_CRT_WARN,  "The current local time is: %s\n", ctime(&seconds) );

	::testing::InitGoogleTest(&argc, argv);
	ret = RUN_ALL_TESTS();
	return ret;
}