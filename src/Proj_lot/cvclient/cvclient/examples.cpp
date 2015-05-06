#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/types_c.h"
#include "opencv2/core/core_c.h"
#include <opencv2/core/core.hpp>
#include "opencv2/opencv.hpp"

#include <vector>   

#include <iostream>
using namespace cv;
using namespace std;

// wykrywanie t³a z wykorzystaniem funkcji grabCut opencv
void detekcja_grabcut()
{
	// READ RGB color image and convert it to Lab
	cv::Mat bgr_image = cv::imread("11.tif"); // BSDS500 mushroom
	cv::imshow("original image", bgr_image);
	//cv::Mat bgr_image_f;
	//bgr_image.convertTo(bgr_image_f, CV_32FC3);

	// define bounding rectangle

	Mat image = bgr_image.clone();
	Mat image2 = image.clone();

	cv::Rect rectangle(40, 90, image.cols - 80, image.rows - 170);

	cv::Mat result; // segmentation result (4 possible values)
	cv::Mat bgModel, fgModel; // the models (internally used)

	// GrabCut segmentation
	cv::grabCut(image,    // input image
		result,   // segmentation result
		rectangle,// rectangle containing foreground
		bgModel, fgModel, // models
		1,        // number of iterations
		cv::GC_INIT_WITH_RECT); // use rectangle
	cout << "oks pa dito" << endl;

	Mat result_a, result_b;
	// Get the pixels marked as background
	cv::compare(result, cv::GC_BGD, result_a, cv::CMP_EQ);
	// Get the pixels marked as likely background
	cv::compare(result, cv::GC_PR_BGD, result_b, cv::CMP_EQ);
	// Final results

	cv::imshow("grabCut", result);
	cv::imshow("Background", result_a);
	cv::imshow("Foreground", result_b);


}

// funkcja normalizacji kolorów
void norm_color()
{

	// Extract the color planes and calculate I = (r + g + b) / 3
	
	cv::Mat bgr_image = cv::imread("11.tif"); // BSDS500 mushroom
	cv::imshow("original image", bgr_image);
	cv::Mat bgr_image_f;
	bgr_image.convertTo(bgr_image_f, CV_32FC3);

	std::vector<cv::Mat> planes(3);
	cv::split(bgr_image_f, planes);

	cv::Mat intensity_f((planes[0] + planes[1] + planes[2]) / 3.0f);
	cv::Mat intensity;
	intensity_f.convertTo(intensity, CV_8UC1);
	cv::imshow("intensity", intensity);

	//void divide(InputArray src1, InputArray src2, OutputArray dst, double scale=1, int dtype=-1)
	cv::Mat b_normalized_f;
	cv::divide(planes[0], intensity_f, b_normalized_f);
	cv::Mat b_normalized;
	b_normalized_f.convertTo(b_normalized, CV_8UC1, 255.0);
	cv::imshow("b_normalized", b_normalized);

	cv::Mat g_normalized_f;
	cv::divide(planes[1], intensity_f, g_normalized_f);
	cv::Mat g_normalized;
	g_normalized_f.convertTo(g_normalized, CV_8UC1, 255.0);
	cv::imshow("g_normalized", g_normalized);

	cv::Mat r_normalized_f;
	cv::divide(planes[2], intensity_f, r_normalized_f);
	cv::Mat r_normalized;
	r_normalized_f.convertTo(r_normalized, CV_8UC1, 255.0);
	//cv::imwrite("02_nor.tif", intensity);
	cv::imshow("r_normalized", r_normalized);
	
}

