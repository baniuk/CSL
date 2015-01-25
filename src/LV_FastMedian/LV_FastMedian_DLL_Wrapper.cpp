/**
 * \file LV_FastMedian_DLL_Wrapper.cpp
 * \brief Implementation of DLL wrapper.
 * \details Exports the following functions:
 * - LV_MedFilt  - Performs median filtering
 * \author PB
 * \date 2015/01/24
 * \version 1.0 Initial version based on ISAR project
 * \version 1.1 Fixed bug #3
 * \version 1.2 Fixed bugs #31, #33
 */

#include "LV_FastMedian/LV_FastMedian_DLL_Wrapper.h"
#include "LV_FastMedian/LV_fastMedian.h"
#include <crtdbg.h>
#include "LV_FastMEdian/errordef.h"

/**
* \brief Performs median filtering of input image
* \details Assumes that input image is 1D array. Any positive and non-zero mask can be used. Returns filtered copy of
* input image (the same size)
* \param[in] input_image 1D input image
* \param[out] output_image	pointer to array of size of input image
* \param[in] nrows	number of rows (height) of input/output image
* \param[in] ncols number of cols (width) of input/output image
* \param[in] mask filter mask uneven and nonzero
* \return operation status, LV_OK on success or error code defined in errordef.h
* \retval uint32_t
* \remarks Returned image has the same size as input image
*/
extern "C" __declspec(dllexport) uint32_t LV_MedFilt(const UINT16* input_image,
	UINT16* output_image,
	UINT16 nrows, UINT16 ncols,
	UINT16 mask)
{
	_ASSERT(input_image);
	_ASSERT(output_image);
	if (0 == mask)
		return IDS_ZEROMASK;
	if (mask < 0)
		return IDS_LESSMASK;
	if (mask % 2 == 0)
		return IDS_EVENMASK;
	OBRAZ obraz;	// lokalna kopia obrazu wejœciowego (p³ytka)
	obraz.tab = input_image;
	obraz.rows = nrows;
	obraz.cols = ncols;
	obraz.tabsize = nrows*ncols;
	FastMedian_Huang(&obraz, output_image, mask);
	return retCode::LV_OK;
}