/**
* \file    LV_Features_DLL_Wrapper.cpp
* \brief	Implementation of DLL wrapper.
* \details Exports the following functions:
* - LV_Features  - Performs thresholding using Savuola method
* \author  PB
* \date    2014/10/10
* \version See LV_Features.cpp
*/

#include <crtdbg.h>
#include "LV_Features/LV_Features.h"
#include "LV_Features/errordef.h"
#include "LV_Features/LV_Features_DLL_Wrapper.h"

/**
TODO \todo Document this method after implementing correct header
*/
extern "C" __declspec(dllexport) uint32_t LV_Features(const UINT16* input_image,
												   UINT16* output_image,
												   UINT16 nrows, UINT16 ncols)
{
	_ASSERT(input_image);
	_ASSERT(output_image);
	/// \todo finish 
	char numOfProc = 1; // fixed number of proceses
	char deb = 0;	// debug off

// 	return Features(C_Image_Container& original,
// 		C_Image_Container& indexed,
// 		C_Image_Container& bw,
// 		C_Matrix_Container& out,
// 		numOfProc,
// 		deb);

}