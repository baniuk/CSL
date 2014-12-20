/**
* \file    dummydllmain.cpp
* \brief	Main entry to DLL
* \details Dummy DLL that will be extended by resource strings and will be 
* tested as input for error handling DLL 
* \author  PB
* \date    2014/12/16
*/

#include <windows.h>
#include <ctime>
#include <crtdbg.h>
#include <definitions.h>
/// Here are definitions of errors
#include "errordef.h"	

BOOL APIENTRY DllMain( HMODULE hModule,
					  DWORD  ul_reason_for_call,
					  LPVOID lpReserved
					  )
{
	HANDLE hLogFile;
	time_t seconds;
	time(&seconds);

	hLogFile = CreateFile("errortestlib.log", FILE_APPEND_DATA,
		FILE_SHARE_WRITE, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, hLogFile);
	_RPT1(_CRT_WARN, "The current local time is: %s\n", ctime(&seconds));

	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		_RPT0(_CRT_WARN, "Free Library");
		break;
	}
	CloseHandle(hLogFile);
	return TRUE;
}

/**
* \brief Fake function in test DLL. Returns given error on request
* \param[in] err numbers from 0 to N
*/
extern "C" __declspec(dllexport) UINT32 bar(int err)
{
	_RPT0(_CRT_WARN, "Entering bar()\n");
	_RPT1(_CRT_WARN, "Error code %d\n", err);
	switch (err)
	{
	case 0:
		return LV_OK;
		break;
	case 1:
		return IDS_ERROR1;
		break;
	case 2:
		return IDS_ERROR2;
		break;
	default:
		return 1000;
	}
}