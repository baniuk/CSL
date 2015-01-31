// cvlib.h : main header file for the cvlib DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include "definitions.h"
#include "setError\setError.h"

extern "C" __declspec(dllexport) void boxes(char *plik);
extern "C" __declspec(dllexport) retCode LV_Sobel(UINT16* inp,UINT16* out,UINT16 rows,UINT16 cols,int dx, int dy,char *errDesc);
extern "C" __declspec(dllexport) retCode LV_Scharr(UINT16* inp,UINT16* out,UINT16 rows,UINT16 cols,int dx, int dy,char *errDesc);
extern "C" __declspec(dllexport) retCode LV_Otsu(UINT16* inp,UINT16* out,UINT16 rows,UINT16 cols,char *errDesc);
extern "C" __declspec(dllexport) retCode LV_Mix(UINT16* inp,UINT16* out,UINT16 rows,UINT16 cols,char *errDesc);

extern "C" __declspec(dllexport) retCode getOutSize(char *plik,UINT16* rows,UINT16 *cols,char *errDesc);
extern "C" __declspec(dllexport) retCode getOut_resize(int rows,int cols,int procx,int procy,int *outx, int *outy, char *errDesc);
extern "C" __declspec(dllexport) retCode LV_resize(UINT16* inp,UINT16* out,UINT16 rows,UINT16 cols,int procx,int procy,char *errDesc);

// CcvlibApp
// See cvlib.cpp for the implementation of this class
//

class CcvlibApp : public CWinApp
{
public:
	CcvlibApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
