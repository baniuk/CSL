/**
* \file    LV_ErrorDecode/dllmain.cpp
* \brief	Main entry to DLL
* \author  PB
* \date    2014/12/18
*/

#include <windows.h>
#include "LV_ErrorDecode/LV_ErrorDecode.h"

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

extern "C" __declspec(dllexport) void getErrorDesc(uint32_t errCode,
	char* errorDescription)
{
	;
}