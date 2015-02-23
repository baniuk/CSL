/**
* \file    M_WeldDetectApprox_DLL_Wrapper.h
* \brief	Warper for dLL file
* \details Wrapper for DLL. Contains only exported method that directly calls methods from static lib
* Only for testing purposes.
* \author  PB
* \date    2014/10/10
* \version see LV_WeldDetectApprox_DLL_Wrapper.cpp
*/

#ifndef M_WeldDetectApprox_DLL_Warper_h__
#define M_WeldDetectApprox_DLL_Warper_h__

#include "definitions.h"
#include <mex.h>
#include <inttypes.h>
#include <opencv2/opencv.hpp>

/// Exported method for weld detection using approximation
void mexFunction(int nlhs,
	mxArray *plhs[],
	int nrhs,
	const mxArray *prhs[]);

#endif // M_WeldDetectApprox_DLL_Warper_h__
