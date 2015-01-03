/**
* \file    LV_WeldDetectApprox_DLL_Wrapper.cpp
* \brief	Implementation of DLL wrapper.
* \details Exports the following functions:
* - LV_WeldDetectApprox  - Performs weld detection using approximation
* \author  PB
* \date    2015/01/03
* \version 1.0 Implementation based on ISAR project with huge code revorking
* \version 1.1 Fixed #35
*/

#include "LV_WeldDetectApprox/LV_WeldDetectApprox_DLL_Wrapper.h"
#include "Geom/C_Point.h"
#include "LV_WeldDetectApprox/ParamEstimation.h"
#include "LV_WeldDetectApprox/C_LinearWeld.h"
#include "LV_WeldDetectApprox/CV_WeldPostProcess.h"
#include "LV_WeldDetectApprox/errordef.h"
#include <memory>

/**
* \brief Exported procedure for werld detection
* \details Detect weld line on radiogram assuming that there are not white frames on image and weld line is moreless
* in the centre part of image. Thicness of the line should be significally smaller than \c y size of the image. In this version there is no extensive
* error checking. It can happen that when weld detection failed the procedure return invalid mask.
* \return operation status, \c LV_OK on success, \c LV_FAIL is returned when the procedure failed on approximation.
* \param[in] input_image 1D input image
* \param[out] output_image	pointer to array of type \c UINT16 of size of input image. It is mask with \c white weld line
* \param[in] nrows	number of rows (height) of input/output image
* \param[in] ncols number of cols (width) of input/output image
* \param[out] errDesc description of the error
* \retval retCode
* \see LV_WeldDetectApprox_tests.cpp
* \see WeldDetecApprox_example.cpp
*/
extern "C" __declspec(dllexport) uint32_t LV_WeldDetectApprox(
	const UINT16* input_image,
	UINT16* output_image,
	UINT16 nrows, UINT16 ncols,
	char* errDesc)
{
	_ASSERT(input_image);
	_ASSERT(output_image);
	UINT16 A, E;
	Matrix_Container rtg;	// temporary object for compatibility
	const std::vector<bool> *_lineOK;	// outputs
	const std::vector<C_WeldPos> *_weldPos;
	// possible external params
	const UINT16 start_x_point = 10; // punkt startowy
	const UINT16 buffor_size = 130;	// wielkość bufora
	const UINT16 step  = 4; // ktok analizy radiogramu
	const double weld_edge = 0.2; // procent amplitudy spawu będący krawędzią

	// settings temprary obj
	// conversion for double is requid=red due to compatibility with old code
	double* image = new double[nrows*ncols];
	for(size_t i=0; i<static_cast<unsigned int>(nrows)*ncols; i++)
		image[i] = static_cast<double>(input_image[i]);

	rtg.data = image;
	rtg._cols = ncols;
	rtg._rows = nrows;

	std::unique_ptr<C_LinearWeld> obj(new C_LinearWeld(&rtg)); // main object
	C_Point cp_x_start(static_cast<double>(start_x_point), 0.0);	// punkt startowy
	ParamEstimation<UINT16>(input_image, ncols, nrows, start_x_point, A, E); // estimation of initial params
	C_LineWeldApprox::setDefaultParams(static_cast<double>(A), 60, 0,
		static_cast<double>(E),
		65535,340,1,70000,
		0,10,-1,-20000); // setting up initial params
	obj->SetProcedureParameters(buffor_size,cp_x_start); // initialize starting point and buffor size
	if (obj->Start(step, 0, weld_edge) == false)
		return IDS_GENERALERROR;

	_lineOK = obj->getLineOK();
	_weldPos = obj->getweldPos();

	cv::Mat cvimage(rtg._rows, rtg._cols, CV_16U, output_image);// rozmiar
	cvimage = cv::Scalar(0);
	fillWeldShape(_weldPos, _lineOK, cvimage);

	delete[] image;
	return retCode::LV_OK;
}