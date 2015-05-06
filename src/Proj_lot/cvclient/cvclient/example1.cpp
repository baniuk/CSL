#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/background_segm.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/types_c.h"
#include "opencv2/core/core_c.h"
#include <opencv2/core/core.hpp>
#include "opencv2/imgproc.hpp"
#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>


// algorytm wykrywania tla - wczeœniejsza wersja opencv
void tlo()
{
	cv::Mat frame;
	cv::Mat back;
	cv::Mat fore;
	cv::VideoCapture cap(0);
	
	cv::Ptr<cv::BackgroundSubtractor> pMOG2; //MOG2 Background subtractor
	pMOG2 = cv::createBackgroundSubtractorMOG2();

	//cv::BackgroundSubtractorMOG2 bg;
	
	
	//bg.nmixtures = 3;
	//bg.bShadowDetection = false;

	std::vector<std::vector<cv::Point> > contours;

	cv::namedWindow("Frame");
	cv::namedWindow("Background");

	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(3, 3));
	//kernel = cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (3, 3))

	for (;;)
	{
		cap >> frame;
		//bg.operator ()(frame, fore);
		//bg.getBackgroundImage(back);
		pMOG2->apply(frame, fore);
		        
		//cv::morphologyEx(fore, fore, cv::MORPH_OPEN, kernel);
		//fgmask = cv2.morphologyEx(fgmask, cv2.MORPH_OPEN, kernel)

		cv::erode(fore, fore, cv::Mat());
		cv::dilate(fore, fore, cv::Mat());
		cv::findContours(fore, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
		cv::drawContours(frame, contours, -1, cv::Scalar(0, 0, 255), 2);
		cv::imshow("Frame", frame);
		cv::imshow("Background", fore);
		//cv::waitKey();
		if (cv::waitKey(30) >= 0) {break; cap.release();};
		
	}
}
