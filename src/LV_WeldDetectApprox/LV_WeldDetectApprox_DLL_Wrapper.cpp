﻿/**
* \file    LV_WeldDetectApprox_DLL_Wrapper.cpp
* \brief	Implementation of DLL wrapper.
* \details Exports the following functions:
* - LV_WeldDetectApprox  - Performs weld detection using approximation
* \author  PB
* \date    2014/10/18
* \version See LV_Threshold.cpp
*/

// #include "LV_Threshold/LV_Threshold.h"
// #include "LV_Threshold/LV_Threshold_DLL_Wrapper.h"

/**
* \brief DLL wrapper for Sauvola thresholding method
* \details Calls directly Sauvola method from static library
* \param[in] input_image 1D input image
* \param[out] output_image	pointer to array of size of input image
* \param[in] nrows	number of rows (height) of input/output image
* \param[in] ncols number of cols (width) of input/output image
* \param[in] w window size (nonzero and uneven)
* \param[in] k Sauvola parameter
* \param[out] errDesc description of the error
* \return operation status, LV_OK on success, LV_FAIL on:
* \li mask equals 0 or is even
* \li image is smaller than mask
* \retval retCode
* \remarks Returned image has the same size as input image
* \see LV_Threshold.cpp
*/
// extern "C" __declspec(dllexport) retCode LV_WeldDetectApprox(	const UINT16* input_image,
// 												   				UINT16* output_image,
// 												   				UINT16 nrows, UINT16 ncols,
// 												   				unsigned int w,
// 												   				double k,
// 												   				char* errDesc)
// {
// 	_ASSERT(input_image);
// 	_ASSERT(output_image);

// 	if(w <= 0)
// 		return setError::throwError("Maska mniejsza lub równa 0", &errDesc);
// 	if( w%2 == 0)
// 		return setError::throwError("Maska parzysta", &errDesc);
// 	if(nrows <= w || ncols <= w)
// 		return setError::throwError("Za duża maska", &errDesc);

// 	Sauv(input_image, output_image, nrows, ncols, w, k);	// wywołanie funkcji
// 	return retCode::LV_OK;
// }