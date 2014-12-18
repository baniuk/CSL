/**
 * \file LV_ErrorDecode.cpp
 * \brief Implementation of ErrorDecode library
 * \details This library translates error codes returned from another libs to
 * description strings. These strings are appended to original DLLs as resurces
 * by means of \a STRINGTABLE fileds. The IDs assigned to strings are also
 * error codes. Every DLLs has assigned certain range of codes, which is
 * globally specified and maintained. All codes returned by such DLL must be in
 * this range.  
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
	if (errCode >= 10000 && errCode < 19999)
		libName = "LV_FastMedian.dll";
	if (errCode >= 20000 && errCode < 29999)
		libName = "LV_Threshold.dll";
	if (errCode >= 30000 && errCode < 39999)
		libName = "LV_WeldDetectApprox.dll";
	return libName;
}

std::string getErrorDescription(uint32_t errCode)
{
	std::string errorDesc;
	std::string libName;
	// check DLL name
	libName = getDllName(errCode);
	if (libName.empty())
	{
		errorDesc = "Unknown error code";
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
	if (retVal != 0)
	{
		std::stringstream sformatted;
		sformatted << "Error of code: " << errCode << " could not be found" <<
			" in library " << libName;
		return errorDesc;
	}
	// found, copy to output
	errorDesc = std::string(buffer);
	return errorDesc;
}
