﻿/**
* \file    LV_Threshold_DLL_Wrapper.h
* \brief	Warper for dLL file
* \detail Wrapper for DLL. Contains only exported method that directly calls methods from static lib
* Only for testing purposes.
* \author  PB
* \date    2014/10/10
*/

#ifndef LV_Threshold_DLL_Warper_h__
#define LV_Threshold_DLL_Warper_h__

#include "setError/setError.h"
#include "definitions.h"

/// Exported method for median filtering using fast median alghoritm
extern "C" __declspec(dllexport) retCode LV_Thresh(const UINT16* input_image,
													UINT16* output_image,
													UINT16 nrows, UINT16 ncols,
													UINT16 mask,
													char* errDesc);
													
#endif // LV_Threshold_DLL_Warper_h__