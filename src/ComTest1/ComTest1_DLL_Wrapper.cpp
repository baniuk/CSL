/**
* \file    ComTest1_DLL_Wrapper.cpp
* \brief	Implementation of DLL wrapper of simple communication test.
* \author  PB
* \date    2014/12/03
*/
#include <windows.h>
#include "ComTest1/ComTest1_DLL_Wrapper.h"
#include <crtdbg.h>
#include <ctime>
#include "MatlabExchange/C_MatlabExchange.hpp"

/**
 * /brief Simple test of DLL to use with LV clusters
 * /details This method saves image provided by LV
 * /param[in] input Input struct defined by LV
 * /remarks /c TD1 struct was created by LabView
 */
extern "C" __declspec(dllexport) void saveImage(TD1* input)
{
	HANDLE hLogFile;
	time_t seconds;
	time(&seconds);
	hLogFile = CreateFile("c:\\ComTest1.log", FILE_APPEND_DATA,
		FILE_SHARE_WRITE, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, hLogFile);

	_RPT1(_CRT_WARN,  "The current local time is: %s\n", ctime(&seconds) );
	_RPT1(_CRT_WARN, "PictureFirstElementAddress %p\n", (UINT16*)input->PictureFirstElementAddress);
	_RPT1(_CRT_WARN, "PictureColumns %d\n", input->PictureColumns);
	_RPT1(_CRT_WARN, "LineWidthPixels %d\n", input->LineWidthPixels);
	_RPT1(_CRT_WARN, "PictureRows %d\n", input->PictureRows);
	_RPT1(_CRT_WARN, "PixelSize in bytes %d\n", input->PixelSizeBytes);

	// nagranie
	C_MatlabExchange image("c:\\comtest1.dat");
	image.AddEntry2D<UINT16>((UINT16*)input->PictureFirstElementAddress,input->PictureRows,input->LineWidthPixels, "image");

	_RPT0(_CRT_WARN, "Detaching");
	CloseHandle(hLogFile);
}