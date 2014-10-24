/**
* \file    LV_WeldDetectApprox_DLL_Wrapper.cpp
* \brief	Implementation of DLL wrapper.
* \details Exports the following functions:
* - LV_WeldDetectApprox  - Performs weld detection using approximation
* \author  PB
* \date    2014/10/18
* \version 
*/

#include "LV_WeldDetectApprox/LV_WeldDetectApprox_DLL_Wrapper.h"

/**
* \brief 
* \details 
* \return operation status, LV_OK on success, LV_FAIL on:
* \retval retCode
*/
 extern "C" __declspec(dllexport) retCode LV_WeldDetectApprox(	const UINT16* input_image,
 												   				UINT16* output_image,
 												   				UINT16 nrows, UINT16 ncols,
 												   				char* errDesc)
{
 	_ASSERT(input_image);
 	_ASSERT(output_image);
 	return retCode::LV_OK;
}