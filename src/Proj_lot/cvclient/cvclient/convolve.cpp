#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;


// moja konwulsja
void convolvelm(char **argv)
{
	Mat zrodlo =  imread(argv[1]);
	
	if (zrodlo.empty()) { cerr << "Brak pliku Ÿród³owego"; return; }
	
	Mat cel;
	Mat kernel(5,5,CV_8S);

	
	for (int i = 0; i < kernel.rows; i++)
		for (int j = 0; j < kernel.cols; j++)
			kernel.at<__int8>(i, j) = -1;

	kernel.at<__int8>(2, 2) = 29;
	
	Point anchor;
	double delta;
	int ddepth;

	anchor = Point(-1, -1);
	delta = 0;
	ddepth = -1;

	filter2D(zrodlo, cel, ddepth, kernel, anchor, delta, BORDER_DEFAULT);
    
	/*
	char* source_window_conv = "Zrodlo";
	namedWindow(source_window_conv, WINDOW_AUTOSIZE);
	imshow(source_window_conv, zrodlo);
	*/

	imshow("Zrodlo", zrodlo);
	imshow("Konwulsja wielkosc 5 jak w imageJ", cel);

	Mat cel2;
	Mat kernel2(3, 3, CV_8S);


	for (int i = 0; i < kernel2.rows; i++)
		for (int j = 0; j < kernel2.cols; j++)
			kernel2.at<__int8>(i, j) = -1;

	kernel2.at<__int8>(1, 1) = 11;
	filter2D(zrodlo, cel2, ddepth, kernel2, anchor, delta, BORDER_DEFAULT);

	imshow("Konwulsja wielkosc 3 jak w LabView", cel2);
	char nazwa[200];
	cout << "Nazwa: " << strlen(argv[1]) << "\n";
	cout << "Dlugosc: " << strlen(argv[1] )-4 << "\n";
	strncpy(nazwa, argv[1], strlen(argv[1] )-4);
	nazwa[strlen(argv[1]) - 4] = 0;
	strcat(nazwa, "_conv5.tif");
	cout << nazwa << "\n";
	char nazwa2[200];
	nazwa2[strlen(argv[1] )-4] = 0;
	strncpy(nazwa2, argv[1], strlen(argv[1]) - 4);
	strcat(nazwa2, "_conv3.tif");
	cout << nazwa2 << "\n";
	imwrite(nazwa, cel);
	imwrite(nazwa2, cel2);

}