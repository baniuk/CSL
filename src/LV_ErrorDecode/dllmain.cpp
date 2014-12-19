/**
* \file    LV_ErrorDecode/dllmain.cpp
* \brief	Main entry to DLL
* \author  PB
* \date    2014/12/18
*/

#include <windows.h>
#include "LV_ErrorDecode/LV_ErrorDecode.h"
#include "definitions.h"

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
* \brief Converts between numeric eror code and its description
* \details Takes numeric error code and converts it to description using
* resources bundled to certain DLL. Correct DLL is loaded looking at error
* codes ranges that identifies all DLL used in project. This method requires
* pointer to char table of size \c MAX_ERROR_STRING defined in definitions.h
* \param[in] errCode numeric error code returned from any DLL
* \param[out] errorDescription description of the error code \c errCode
* \return Description of the error
* \retval \c void
* \author PB
* \date 2014/12/19
* \see LV_ErrorDecode.h
* \copydetails LV_ErrorDecode.h
*/
extern "C" __declspec(dllexport) void getErrorDesc(uint32_t errCode,
	char* errorDescription)
{
	std::string errDesc;
	errDesc = getErrorDescription(errCode);
	// errDesc na pewno jest przyciêty przez funkcjê getErrorDescription
	std::strcpy(errorDescription, errDesc.c_str()); 
}