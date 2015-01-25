/**
 * \file LV_FastMedian_DLL_Wrapper.h
 * \brief Warper for dLL file
 * \details Wrapper for DLL. Contains only exported method that directly calls methods from static lib
 * Only for testing purposes.
 * \author PB
 * \date 2015/01/24
 * \version see LV_FastMedian_DLL_Wrapper.cpp
 */

#ifndef LV_FastMedian_DLL_Wrapper_h__
#define LV_FastMedian_DLL_Wrapper_h__

#include "definitions.h"
#include <inttypes.h>

extern "C" __declspec(dllexport) uint32_t LV_MedFilt(const UINT16* input_image,
	UINT16* output_image,
	UINT16 nrows, UINT16 ncols,
	UINT16 mask);

#endif // LV_FastMedian_DLL_Wrapper_h__