/**
* \file   LV_WeldDetectApprox_WeldPostProcess_tests.cpp
* \brief	Tests for weld postprocessing based on OpenCV
* \author  PB
* \date    2014/10/25
*/

#include "gtest/gtest.h"
#include "definitions.h"
#include "LV_WeldDetectApprox/CV_WeldPostProcess.h"
#include "MatlabExchange/C_MatlabExchange.hpp"

/**
* \test WeldPostProcess, _getRawPointer
* \brief Gets raw pointer from OpenCV structures
* \details Creates simple OpenCV image and then saves it as Matlab data
* \pre -
* \post \c weldpostprocess.out file with that contains the same image as \c test.png
* \author PB
* \date 2014/10/28
*/
TEST(WeldPostProcess, _getRawPointer)
{
	// obraz testowy
	Mat image(100,100, CV_16U, Scalar(0));
	vector<Point> fillContSingle;
	fillContSingle.push_back(Point(0,0));
	fillContSingle.push_back(Point(0,50));
	fillContSingle.push_back(Point(50,50));
	fillContSingle.push_back(Point(50,0));

	vector<vector<Point>> fillContAll;
	fillContAll.push_back(fillContSingle);
	cv::fillPoly( image, fillContAll, cv::Scalar(65535));
	cv::imwrite("test.png", image);

	// konversja i nagrywanie
	UINT16* outImage;
	UINT16 rows, cols;
	retCode ret;
	ret = getRawPointer(image, &outImage, rows, cols);
	ASSERT_EQ(ret, LV_OK);

	C_MatlabExchange dump("weldpostprocess.out");
	dump.AddEntry2D<UINT16>(outImage, rows, cols,"fillpolygon");

	delete[] outImage;
}