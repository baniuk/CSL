/**
 * \file LV_Features_DLL_Wrapper.h
 * \brief Warper for dLL file
 * \details Wrapper for DLL. Contains only exported method that directly calls methods from static lib
 * Only for testing purposes.
 * \author PB
 * \date 2015/02/03
 * \version see LV_Features_DLL_Wrapper.cpp
 */

#ifndef LV_Features_DLL_Wrapper_h__
#define LV_Features_DLL_Wrapper_h__

#include "definitions.h"
#include <inttypes.h>

/// \todo This is only fake method - implement correct one
extern "C" __declspec(dllexport) uint32_t LV_Features(const UINT16* input_image,
												   UINT16* output_image,
												   UINT16 nrows, UINT16 ncols,
												   unsigned int w,
												   double k,
												   char* errDesc);

#endif // LV_Features_DLL_Wrapper_h__