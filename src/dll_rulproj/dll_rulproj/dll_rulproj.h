// dll_rulproj.h : main header file for the dll_rulproj DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

extern "C" __declspec(dllexport) int generuj_klasy(double *dane,long rows,long cols,int *wynik);
extern "C" __declspec(dllexport) int generuj_klasy_plik(char *nazwa,int *wynik);

// Cdll_rulprojApp
// See dll_rulproj.cpp for the implementation of this class
//

class Cdll_rulprojApp : public CWinApp
{
public:
	Cdll_rulprojApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
