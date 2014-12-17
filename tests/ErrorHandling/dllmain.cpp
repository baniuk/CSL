/**
* \file    ErrorHandling/dllmain.cpp
* \brief	Main entry to DLL
* \details Dummy DLL that will be extended by resource strings and will be 
* tested as input for error handling DLL 
* \author  PB
* \date    2014/12/16
*/

#include <windows.h>
#include <definitions.h>
#include "errordef.h"

BOOL APIENTRY DllMain( HMODULE hModule,
					  DWORD  ul_reason_for_call,
					  LPVOID lpReserved
					  )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

/**
* \brief Fake function in test DLL. Returns given error on request
* \param[in] err numbers from 0 to N
*/
extern "C" __declspec(dllexport) UINT32 bar(int err)
{
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