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
* \test STATIC_WeldPostProcess, _getRawPointer
* \brief Gets raw pointer from OpenCV structures
* \details Creates simple OpenCV image and then saves it as Matlab data
* \pre -
* \post \c weldpostprocess.out file with that contains the same image as \c test.png
* \author PB
* \date 2014/10/28
*/
TEST(STATIC_WeldPostProcess, _getRawPointer)
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
	std::unique_ptr<UINT16[]> outImage;
	UINT16 rows, cols;
	retCode ret;
	ret = getRawPointer(image, outImage, rows, cols);
	ASSERT_EQ(ret, LV_OK);

	C_MatlabExchange dump("weldpostprocess.out");
	dump.AddEntry2D<UINT16>(outImage.get(), rows, cols,"fillpolygon");
}

/**
* \test STATIC_WeldPostProcess, _fillWeldShape
* \brief Fills weld line
* \details Runs \c fillWeldShape method to obtain filled weld shape. First preapare test data reading them from disk and previous tests
* \pre Output data from WeldDetectApprox_1 test with C_WeldPos structures
* \li D_WeldDetexApprox_1.dat
* \li G_WeldDetexApprox_1.dat
* \li lineok_WeldDetexApprox_1.dat
* \post image \c filled_weld.png
* \author PB
* \date 2014/10/30
*/
TEST(STATIC_WeldPostProcess, _fillWeldShape)
{
	// wczytanie gotowych pozycji z C_WeldPos z przyk³adu 1
	std::unique_ptr<double[]> D;
	std::unique_ptr<double[]> G;
	std::unique_ptr<double[]> lineok;
	unsigned int rows, cols;
	ASSERT_NO_THROW(C_MatlabExchange::ReadData("D_WeldDetexApprox_1.dat", D, rows, cols));
	ASSERT_NO_THROW(C_MatlabExchange::ReadData("G_WeldDetexApprox_1.dat", G, rows, cols));
	ASSERT_NO_THROW(C_MatlabExchange::ReadData("lineok_WeldDetexApprox_1.dat", lineok, rows, cols));
	// recreate C_WeldPos
	std::vector<C_WeldPos> wp;
	std::vector<bool> line;
	C_WeldPos _wp;
	bool _lineok;
	for(size_t i=0,p=0;i<cols;++i,p+=2) // lineok jest wektorem ,wszedzie ta sama zmienna
	{
		_wp.G.setPoint(G[p], G[p+1]);
		_wp.S.setPoint(0,0);
		_wp.D.setPoint(D[p], D[p+1]);
		_lineok = static_cast<bool>(lineok[i]);

		wp.push_back(_wp);
		line.push_back(_lineok);
	}

	cv::Mat image(1848, 4634, CV_16U, Scalar(0));// rozmiar testimag1
	fillWeldShape(&wp, &line, image);
	cv::imwrite("filled_weld.png", image);
}