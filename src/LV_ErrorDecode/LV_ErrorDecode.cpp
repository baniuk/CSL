/**
 * \file LV_ErrorDecode.cpp
 * \brief Implementation of ErrorDecode library
 * \see LV_ErrorDecode.h for details
 * \author PB
 * \date 2014/12/18
 * \version 1.0
 */

#include <windows.h>
#include <sstream>
#include "LV_ErrorDecode/LV_ErrorDecode.h"
#include "definitions.h"

std::string getDllName(uint32_t errCode)
{
	std::string libName;
	libName.clear();
	// decode
	if (errCode >= 0x01000000 && errCode <= 0x010000FF)
		libName = "LV_FastMedian.dll";
	if (errCode >= 0x02000000 && errCode <= 0x020000FF)
		libName = "LV_Threshold.dll";
	if (errCode >= 0x03000000 && errCode <= 0x030000FF)
		libName = "LV_WeldDetectApprox.dll";
	if (errCode >= 0x04000000 && errCode <= 0x040000FF)
		libName = "LV_Features.dll";
	if (errCode >= 0xFFFFFF00 && errCode < 0xFFFFFFFE)
		libName = "LV_ErrorDecode_dummyDLL.dll";
	return libName;
}

std::string getErrorDescription(uint32_t errCode)
{
	std::string errorDesc;
	std::string libName;
	if (errCode == LV_OK)
	{
		errorDesc = "No error";
		return errorDesc;
	}
	// check DLL name
	libName = getDllName(errCode);
	if (libName.empty())
	{
		errorDesc = "Unknown error code. Can not connect with any known library";
		return errorDesc;
	}
	// if library found try to load it
	HINSTANCE hinstLib;
	hinstLib = LoadLibrary(libName.c_str());
	if (hinstLib == NULL)
	{
		std::stringstream sformatted;
		sformatted << "library " << libName << " could not be found";
		errorDesc = sformatted.str();
		return errorDesc;
	}
	// lib loaded
	char buffer[MAX_ERROR_STRING];
	int retVal;
	retVal = LoadString(hinstLib,
		errCode,
		buffer,
		MAX_ERROR_STRING);
	FreeLibrary(hinstLib);
	if (retVal == 0)
	{
		std::stringstream sformatted;
		sformatted << "Error of code: " << std::hex << errCode << " could not be found" <<
			" in library " << libName;
		errorDesc = sformatted.str();
		return errorDesc;
	}
	// found, copy to output
	errorDesc = std::string(buffer);
	return errorDesc;
}
