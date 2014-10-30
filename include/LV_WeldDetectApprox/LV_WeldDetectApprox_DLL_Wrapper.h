﻿/**
* \file    LV_WeldDetectApprox_DLL_Wrapper.h
* \brief	Warper for dLL file
* \details Wrapper for DLL. Contains only exported method that directly calls methods from static lib
* Only for testing purposes.
* \author  PB
* \date    2014/10/10
*/

#ifndef LV_WeldDetectApprox_DLL_Warper_h__
#define LV_WeldDetectApprox_DLL_Warper_h__

#include "setError/setError.h"
#include "definitions.h"
#include <opencv2/opencv.hpp>

/// Exported method for weld detection using approximation
extern "C" __declspec(dllexport) retCode LV_WeldDetectApprox(	const UINT16* input_image,
															 UINT16* output_image,
															 UINT16 nrows, UINT16 ncols,
															 char* errDesc);

#endif // LV_WeldDetectApprox_DLL_Warper_h__
