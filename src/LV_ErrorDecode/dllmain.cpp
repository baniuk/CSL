/**
* \file    LV_ErrorDecode/dllmain.cpp
* \brief	Main entry to DLL
* \author  PB
* \date    2014/12/18
*/

#include <windows.h>
#include "LV_ErrorDecode/LV_ErrorDecode.h"
#include "definitions.h"

/// Defines boundary size of string for safety reasons
#define MaxHandleStringLength INT32_MAX

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
	std::string errDesc;
	errDesc = getErrorDescription(errCode);
	// errDesc na pewno jest przyciêty przez funkcjê getErrorDescription
	std::strcpy(errorDescription, errDesc.c_str()); 
}


extern "C" __declspec(dllexport) void LV_getErrorDesc(uint32_t errCode,
	LStrHandle errorDescription)
{
	std::string errDesc;
	int32 len;
	errDesc = getErrorDescription(errCode);
	// d³ugoœæ ³añcucha
	len = errDesc.length();
	// boundary limit
	if (len > MaxHandleStringLength)
		len = MaxHandleStringLength;
	if (!DSCheckHandle(errorDescription))	// valid handle
	{
		DSSetHandleSize((void*)errorDescription, len);	// set new handle size
		StrNCpy((*errorDescription)->str, (ConstCStr)errDesc.c_str(), len);
		(*errorDescription)->cnt = len;		
	}


}