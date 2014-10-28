/**
* \file   CV_WeldPostProcess.h
* \brief	Prototypes for basic OpenCV based method related to WeldDetection
* \author  PB
* \date    2014/10/25
*/
#ifndef CV_WeldPostProcess_h__
#define CV_WeldPostProcess_h__

#include <opencv2/opencv.hpp>
#include "definitions.h"
#include <memory>
#include <climits>
#include <crtdbg.h>
#include "LV_WeldDetectApprox/C_LinearWeld.h"

using namespace cv;
using namespace std;

/// Fills shape of the weld
void fillWeldShape(const vector<C_WeldPos>* _weldpos, const std::vector<bool>* _lineOK, UINT16 nrows, UINT16 ncols);
/// Converts OpenCV image to raw table
retCode getRawPointer(const cv::Mat& image, unique_ptr<UINT16[]>& p_raw, UINT16& rows, UINT16& cols);
#endif // CV_WeldPostProcess_h__