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
#include <climits>
#include <crtdbg.h>

using namespace cv;
using namespace std;

/// Fills shape of the weld
void fillWeldShape(UINT16** data, unsigned int& rows, unsigned int& cols);
/// Converts OpenCV image to raw table
retCode getRawPointer(const cv::Mat& image, UINT16** p_raw, UINT16& rows, UINT16& cols);
#endif // CV_WeldPostProcess_h__