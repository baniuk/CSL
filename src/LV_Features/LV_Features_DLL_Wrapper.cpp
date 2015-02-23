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
* \brief Exported procedure fetaures evaluation
* \details Computes set of features basing on input image that must be provided in three forms.
* \li original image
* \li indexed image
* \li binary image
* 
* Features are calculated for all obiects found in binary image and numbered in accordance to 
* indexed image.
* 
* \return operation status, \c LV_OK on success, \c LV_FAIL is returned when the procedure failed.
* \param[in] input_image 1D input image.
* \param[in] bw_image thresholded \c input_image
* \param[in] indexed_image indexed \c bw_image
* \param[out] output_data table of fixed size Nx71, where \c N is the number of unique objects in image
* This vale can be read from indexed image as largest unique number -1
* \param[in] nrows	number of rows (height) of input image
* \param[in] ncols number of cols (width) of input image
* \retval uint32_t
*/
extern "C" __declspec(dllexport) uint32_t LV_Features(
	const UINT16* input_image,
	const UINT16* bw_image,
	const UINT16* indexed_image,
	double* output_data,
	UINT16 nrows, UINT16 ncols)
{
	_ASSERT(input_image);
	_ASSERT(output_data);

	char numOfProc = 1; // fixed number of proceses
	char deb = 0;	// debug off
	uint32_t ret;
	// konwersja na containery
	C_Image_Container input_image_;
	C_Image_Container bw_image_;
	C_Image_Container indexed_image_;
	C_Matrix_Container output_data_;

	input_image_.AllocateData(nrows, ncols);
	for (size_t i = 0; i < input_image_.GetNumofElements(); ++i)
		input_image_.data[i] = static_cast<double>(input_image[i]);

	bw_image_.AllocateData(nrows, ncols);
	for (size_t i = 0; i < bw_image_.GetNumofElements(); ++i)
		bw_image_.data[i] = static_cast<double>(bw_image[i]);

	indexed_image_.AllocateData(nrows, ncols);
	for (size_t i = 0; i < indexed_image_.GetNumofElements(); ++i)
		indexed_image_.data[i] = static_cast<double>(indexed_image[i]);

	ret = Features(input_image_, indexed_image_, bw_image_, output_data_, numOfProc, deb);

	// assume that output has correct size
	for (size_t i = 0; i < output_data_.GetNumofElements(); ++i)
		output_data[i] = output_data_.data[i];


	return ret;

}