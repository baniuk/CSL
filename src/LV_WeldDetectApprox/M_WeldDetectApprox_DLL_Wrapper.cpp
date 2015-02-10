/**
* \file    M_WeldDetectApprox_DLL_Wrapper.cpp
* \brief	Implementation of DLL wrapper for Matlab.
* \details Exports the following functions:
* - LV_WeldDetectApprox  - Performs weld detection using approximation
* \author  PB
* \date    2015/01/03
*/

#include "LV_WeldDetectApprox/M_WeldDetectApprox_DLL_Wrapper.h"
#include "Geom/C_Point.h"
#include "LV_WeldDetectApprox/ParamEstimation.h"
#include "LV_WeldDetectApprox/C_LinearWeld.h"
#include "LV_WeldDetectApprox/CV_WeldPostProcess.h"
#include "LV_WeldDetectApprox/errordef.h"
#include <memory>

/**
* \brief Exported procedure for weld detection under Matlab
* /see LV_WeldDetectApprox_DLL_Wrapper.cpp
*/
void mexFunction(int nlhs,
	mxArray *plhs[],
	int nrhs,
	const mxArray *prhs[])
{
	if(nrhs!=1)
        mexErrMsgIdAndTxt("M_WeldDetectApprox:IOError","One input required.");
    if(nlhs!=1)
        mexErrMsgIdAndTxt("M_WeldDetectApprox:IOError","One output required.");
	if (mxGetClassID(prhs[0]) != mxDOUBLE_CLASS)
    	mexErrMsgIdAndTxt("M_WeldDetectApprox:IOError","Input must be DOUBLE class scalled to UINT range.");

	size_t a;
	size_t rows = mxGetM(prhs[0]);
	size_t cols = mxGetN(prhs[0]);
	double* m_input = mxGetPr(prhs[0]);

	// output
	UINT16* output_image = new UINT16[rows*cols];
	// local copy of prhs[0]
	double* input_image = new double[rows*cols];
	// konwersja zols -> rows
	a = 0;
	for (size_t c = 0; c < cols; c++)
		for (size_t r = 0; r < rows; r++)
			input_image[r*cols + c] = m_input[a++];

	// debug - copy in->out
	for (size_t i = 0; i < rows*cols; i++)
		output_image[i] = input_image[i];

 	double A, E;
 	Matrix_Container rtg;	// temporary object for compatibility
 	const std::vector<bool> *_lineOK;	// outputs
 	const std::vector<C_WeldPos> *_weldPos;
 	// possible external params
 	const UINT16 start_x_point = 10; // punkt startowy
 	const UINT16 buffor_size = 130;	// wielkość bufora
 	const UINT16 step  = 4; // ktok analizy radiogramu
 	const double weld_edge = 0.2; // procent amplitudy spawu będący krawędzią

	rtg.data = input_image;
	rtg._cols = cols;
	rtg._rows = rows;
 
  	std::unique_ptr<C_LinearWeld> obj(new C_LinearWeld(&rtg)); // main object
  	C_Point cp_x_start(static_cast<double>(start_x_point), 0.0);	// punkt startowy
  	ParamEstimation<double>(input_image, cols, rows, start_x_point, A, E); // estimation of initial params
  	C_LineWeldApprox::setDefaultParams(static_cast<double>(A), 60, 0,
  		static_cast<double>(E),
  		65535,340,1,70000,
  		0,10,-1,-20000); // setting up initial params
  	obj->SetProcedureParameters(buffor_size,cp_x_start); // initialize starting point and buffor size
  	if (obj->Start(step, 0, weld_edge) == false)
 		mexErrMsgIdAndTxt("M_WeldDetectApprox:Start", "Error in Start().");
  
  	_lineOK = obj->getLineOK();
  	_weldPos = obj->getweldPos();
  
  	cv::Mat cvimage(rtg._rows, rtg._cols, CV_16U, output_image);// rozmiar
  	cvimage = cv::Scalar(0);
  	fillWeldShape(_weldPos, _lineOK, cvimage);
 
 	plhs[0] = mxCreateDoubleMatrix(rtg._rows,rtg._cols,mxREAL);
 	double*	p_out = mxGetPr(plhs[0]);
	// copy from local array to matlab array columns ordred)
	for (size_t c = 0, a = 0; c < cols; c++)
		for (size_t r = 0; r < rows; r++)
			p_out[a++] = output_image[r*cols + c];
			
	delete[] input_image;
	delete[] output_image;
}