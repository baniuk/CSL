//opencv
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/background_segm.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/types_c.h"
#include "opencv2/core/core_c.h"
#include <opencv2/core/core.hpp>
//C
#include <stdio.h>
//C++
#include <iostream>
#include <sstream>

using namespace cv;
using namespace std;


// przyk³ad segmentacji obrazu OTSU
void watershed1()
{

	Mat img = cv::imread("11.tif");
	Mat gray, thresh;
	cv::cvtColor(img, gray, COLOR_BGR2GRAY);
	cv::threshold(gray, thresh, 0, 255, THRESH_BINARY_INV + THRESH_OTSU);
	
	imshow("Orginal", img);
	imshow("Thresh", thresh);

    //ret, thresh = cv2.threshold(gray, 0, 255, cv2.THRESH_BINARY_INV + cv2.THRESH_OTSU)


}



// przyk³ad segmentacji obrazu OTSU + usuniecie szumow + otwarcie + dylatacja + t³o
void watershed2()
{
	Mat img = cv::imread("13.tif");
	Mat gray, thresh;
	cv::cvtColor(img, gray, COLOR_BGR2GRAY);
	cv::threshold(gray, thresh, 0, 255, THRESH_BINARY_INV + THRESH_OTSU);

	imshow("Orginal", img);
	imshow("Thresh", thresh);
	
	// noise removal
	Mat kernel = Mat::ones(cv::Size(3, 3), CV_8U);
	Mat opening;
	cv::morphologyEx(thresh, opening, MORPH_OPEN, kernel, cv::Point(-1,-1), 2);
	//kernel = np.ones((3, 3), np.uint8)
	//opening = cv2.morphologyEx(thresh, cv2.MORPH_OPEN, kernel, iterations = 2)
	
	imshow("opening", opening);
	
	//sure background area
	Mat sure_bg;
	cv::dilate(opening, sure_bg, kernel, cv::Point(-1, -1), 3);
	imshow("sure_bg", sure_bg);
	//sure_bg = cv2.dilate(opening, kernel, iterations = 3)
	  
	//Finding sure foreground area
	Mat dist_transform;
	cv::distanceTransform(opening, dist_transform, CV_DIST_L2, 3);
    
	Mat sure_fg;
	cv::threshold(dist_transform, sure_fg, 0, 255, 0);
	imshow("dist_transform", dist_transform);
	imshow("sure_fg", sure_fg);

	//dist_transform = cv2.distanceTransform(opening, cv2.DIST_L2, 5)
	//ret, sure_fg = cv2.threshold(dist_transform, 0.7*dist_transform.max(), 255, 0)
	
    // Finding unknown region
	
	
	//cv::cvtColor(sure_fg, sure_fg, 0);
	sure_fg.convertTo(sure_fg, CV_8U);
	cout << "Typ sure_fg:" << sure_fg.type() << " typ sure_bg: " << sure_bg.type() << "\n";
	Mat unknown;
	cv::subtract(sure_bg, sure_fg, unknown);
	
	imshow("sure_fg1", sure_fg);
	imshow("unknown", unknown);

	/*
     	sure_fg = np.uint8(sure_fg)
	    unknown = cv2.subtract(sure_bg, sure_fg)
     */
}