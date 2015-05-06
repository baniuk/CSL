#include "stdafx.h"
#include "cvprocess.h"

#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/types_c.h"
#include "opencv2/core/core_c.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

using namespace cv;

/*! \file cvprocess.cpp
\brief Plik z funkcjami do podstawowych operacji przetwarzania obrazu na potrzeby wytworzenia biblioteki cvlib.dll dla LabView
\details Dostêpne s¹ nastêpuj¹ce funkcje:<br/>
UINT16 CV_brightness(UINT16* inp, UINT16* out, UINT16 rows, UINT16 cols, double alpha, int beta);<br/>
funkcja dla zmiany jasnoœci oraz kontrastu<br/>
UINT16 CV_convolve(UINT16* inp, UINT16* out, UINT16 rows, UINT16 cols,int kerneltype);<br/>
funkcja s³u¿y do wykonania tak zwanej operacji konturowania (ang.convolve)<br/>
UINT16 CV_morphpology(UINT16* inp, UINT16* out, UINT16 rows, UINT16 cols, int operation, int kerneltype, int kernsize);<br/>
funkcja s³u¿y do wykonania operacji morfologicznych takich jak: otwarcie, zamkniêcie, gradient, operacja tzw. "Top Hat", operacja tzw. "Black Hat"<br/>
UINT16 CV_watershed(UINT16* inp, UINT16* out, UINT16 rows, UINT16 cols);<br/>
funkcja s³u¿y do wykonania operacji segmentacji tzw. rozlewowej (ang. watershed)<br/>
UINT16 CV_erosion(UINT16* inp, UINT16* out, UINT16 rows, UINT16 cols, int kerneltype, int kernelsize);<br/>
funkcja s³u¿y do wykonania operacji erozji<br/>
UINT16 CV_dilation(UINT16* inp, UINT16* out, UINT16 rows, UINT16 cols, int kerneltype, int kernelsize);<br/>
funkcja s³u¿y do wykonania operacji dylatacji<br/>
UINT16 CV_smooth(UINT16* inp, UINT16* out, UINT16 rows, UINT16 cols, int type, int kernellength);<br/>
funkcja s³u¿y do wykonania operacji wyg³adzenia (rozmycia)<br/>
\author LM
*/




/** @function CV_brightness
\brief funkcja s³u¿y do zmiany wielkoœci jasnoœci oraz kontrastu
\param [in] inp - wskaŸnik na obraz wejœciowy (musi byæ zarezerwowany przed u¿yciem funkcji)
\param [out] out - wskaŸnik na obraz wyjœciowy (musi byæ zarezerwowany przed u¿yciem funkcji)
\param [in] rows - ilosc wierszy w obrazie wejœciowym i wyjœciowym
\param [in] cols - ilosc wierszy w obrazie wejœciowym i wyjœciowym
\param [in] alpha - parametr zmiennoprzecinkowy okreœlaj¹cy poziom kontrastu
\param [in] beta - parametr sta³oprzecinkowy okreœlaj¹cy poziom jasnoœci
\return zwraca wynik dzia³ania funkcji: 0 - oznacza poprawne zakoñczenie, >0 oznacza odpowiedni b³¹d
\author LM
*/
UINT16 CV_brightness(UINT16* inp, UINT16* out, UINT16 rows, UINT16 cols, double alpha, int beta)
{
	
	try
	{
	Mat image = Mat(rows, cols, CV_8UC3, inp).clone();
	Mat new_image = Mat::zeros(image.size(), image.type());

	//operacja dostrojenia jasnosci i kontrastu  new_image(i,j) = alpha*image(i,j) + beta
	for (int y = 0; y < image.rows; y++) {
		for (int x = 0; x < image.cols; x++) {
			for (int c = 0; c < 3; c++) {
				new_image.at<Vec3b>(y, x)[c] =
					saturate_cast<uchar>(alpha*(image.at<Vec3b>(y, x)[c]) + beta);
			}
		}
	}

	new_image.convertTo(new_image, CV_8UC3);
	memcpy(out, new_image.data, new_image.total() * new_image.elemSize());
	}
	catch (Exception &e)
	{
		std::string tekst1 = e.what();
		return 1;
	}

	return 0;

}

/** @function CV_convolve
\brief funkcja s³u¿y do wykonania tak zwanej operacji konturowania (ang.convolve)
\param [in] inp - wskaŸnik na obraz wejœciowy (musi byæ zarezerwowany przed u¿yciem funkcji)
\param [out] out - wskaŸnik na obraz wyjœciowy (musi byæ zarezerwowany przed u¿yciem funkcji)
\param [in] rows - ilosc wierszy w obrazie wejœciowym i wyjœciowym
\param [in] cols - ilosc wierszy w obrazie wejœciowym i wyjœciowym
\param[in] kerneltype - typ j¹dra 1 - j¹dro 3x3 wymiarowe: wartoœci -1 œrodek 11, typ j¹dra 2 - j¹dro 5x5 wymiarowe: wartoœci -1 œrodek 29
\return zwraca wynik dzia³ania funkcji: 0 - oznacza poprawne zakoñczenie, >0 oznacza odpowiedni b³¹d
\author LM
*/
UINT16 CV_convolve(UINT16* inp, UINT16* out, UINT16 rows, UINT16 cols,int kerneltype)
{
	try
	{
	  Mat kernel;
	// weryfikacja parametru wejœciowego
	if (kerneltype == 1)
	{
		kernel.create(3, 3, CV_8S);
		for (int i = 0; i < kernel.rows; i++)
			for (int j = 0; j < kernel.cols; j++)
				kernel.at<__int8>(i, j) = -1;

		kernel.at<__int8>(1, 1) = 11;
		
	}
	else if (kerneltype == 2)
	{
		kernel.create(5, 5, CV_8S);
		for (int i = 0; i < kernel.rows; i++)
			for (int j = 0; j < kernel.cols; j++)
				kernel.at<__int8>(i, j) = -1;
		kernel.at<__int8>(2, 2) = 29;
	}
	else
		return 1; //B³êdy parametr j¹dra

	Mat image = Mat(rows, cols, CV_8UC3, inp).clone();
	Mat new_image;
	Point anchor = Point(-1, -1);
	double delta = 0;
	int ddepth = -1;

	filter2D(image, new_image, ddepth, kernel, anchor, delta, BORDER_DEFAULT);
	new_image.convertTo(new_image, CV_8UC3);
	memcpy(out, new_image.data, new_image.total() * new_image.elemSize());
	
	} // od try
	catch (Exception &e)
	{
		std::string tekst1 = e.what();
		return 1;
	}

	return 0;


}

/** @function CV_morphpology
\brief funkcja s³u¿y do wykonania operacji morfologicznych takich jak: otwarcie, zamkniêcie, gradient, operacja tzw. "Top Hat", operacja tzw. "Black Hat"
\param [in] inp - wskaŸnik na obraz wejœciowy (musi byæ zarezerwowany przed u¿yciem funkcji)
\param [out] out - wskaŸnik na obraz wyjœciowy (musi byæ zarezerwowany przed u¿yciem funkcji)
\param [in] rows - ilosc wierszy w obrazie wejœciowym i wyjœciowym
\param [in] cols - ilosc wierszy w obrazie wejœciowym i wyjœciowym
\param [in] operation - operacja morfologiczna: 0 - otwarcie, 1 - zamkniêcie, 2 - gradient, 3 - operacja tzw. "Top Hat", 4 - operacja tzw. "Black Hat"
\param [in] kerneltype - wybór j¹dra dla opercji morfologicznej: 0 - prostok¹t, 1 - krzy¿, 2 - elipsa
\param [in] kernsize - wielkoœæ j¹dra: = 2*kernsize + 1, nie wiêcej ni¿ 21
\return zwraca wynik dzia³ania funkcji: 0 - oznacza poprawne zakoñczenie, >0 oznacza odpowiedni b³¹d
\author LM
*/
UINT16 CV_morphpology(UINT16* inp, UINT16* out, UINT16 rows, UINT16 cols, int operation, int kerneltype, int kernsize)
{
	try
	{
		int morph_elem = kerneltype;
		int morph_size = kernsize;
		int morph_operator = 0;
		int const max_operator = 4;
		int const max_elem = 2;
		int const max_kernel_size = 21;

		//walidacja 
		if (operation > max_operator || kerneltype > max_elem || kernsize > max_kernel_size)
		{
			return 1;
		}
		
		Mat image = Mat(rows, cols, CV_8UC3, inp).clone();
		Mat new_image;
		int operation1 = operation + 2;
		
		Mat element = getStructuringElement(morph_elem, Size(2 * morph_size + 1, 2 * morph_size + 1), Point(morph_size, morph_size));

		/// Apply the specified morphology operation
		morphologyEx(image, new_image, operation1, element);
		
		new_image.convertTo(new_image, CV_8UC3);
		memcpy(out, new_image.data, new_image.total() * new_image.elemSize());

	} // od try
	catch (Exception &e)
	{
		std::string tekst1 = e.what();
		return 1;
	}

	return 0;
}

class WatershedSegmenter{
private:
	cv::Mat markers;
public:
	void setMarkers(cv::Mat& markerImage)
	{
		markerImage.convertTo(markers, CV_32S);
	}

	cv::Mat process(cv::Mat &image)
	{
		cv::watershed(image, markers);
		markers.convertTo(markers, CV_8U);
		return markers;
	}
};


/** @function CV_watershed
\brief funkcja s³u¿y do wykonania operacji segmentacji tzw. rozlewowej (ang. watershed)
\param [in] inp - wskaŸnik na obraz wejœciowy (musi byæ zarezerwowany przed u¿yciem funkcji)
\param [out] out - wskaŸnik na obraz wyjœciowy (musi byæ zarezerwowany przed u¿yciem funkcji)
\param [in] rows - ilosc wierszy w obrazie wejœciowym i wyjœciowym
\param [in] cols - ilosc wierszy w obrazie wejœciowym i wyjœciowym
\return zwraca wynik dzia³ania funkcji: 0 - oznacza poprawne zakoñczenie, >0 oznacza odpowiedni b³¹d
\author LM
*/
UINT16 CV_watershed(UINT16* inp, UINT16* out, UINT16 rows, UINT16 cols)
{
	try
	{
		Mat image = Mat(rows, cols, CV_8UC3, inp).clone();
		Mat new_image;
		cv::Mat binary;// = cv::imread(argv[2], 0);
		cv::cvtColor(image, binary, CV_BGR2GRAY);
		cv::threshold(binary, binary, 100, 255, THRESH_BINARY);
				
		// Eliminate noise and smaller objects
		cv::Mat fg;
		cv::erode(binary, fg, cv::Mat(), cv::Point(-1, -1), 2);
		
		// Identify image pixels without objects
		cv::Mat bg;
		cv::dilate(binary, bg, cv::Mat(), cv::Point(-1, -1), 3);
		cv::threshold(bg, bg, 1, 128, cv::THRESH_BINARY_INV);
		
		// Create markers image
		cv::Mat markers(binary.size(), CV_8U, cv::Scalar(0));
		markers = fg + bg;
		
		// Create watershed segmentation object
		WatershedSegmenter segmenter;
		segmenter.setMarkers(markers);

		cv::Mat result = segmenter.process(image);
		result.convertTo(result, CV_8U);
		cvtColor(result, new_image, CV_GRAY2RGB);
		
		memcpy(out, new_image.data, new_image.total() * new_image.elemSize());

	} // od try
	catch (Exception &e)
	{
		std::string tekst1 = e.what();
		return 1;
	}
	
	return 0;

}

/** @function CV_erosion
\brief funkcja s³u¿y do wykonania operacji erozji
\param [in] inp - wskaŸnik na obraz wejœciowy (musi byæ zarezerwowany przed u¿yciem funkcji)
\param [out] out - wskaŸnik na obraz wyjœciowy (musi byæ zarezerwowany przed u¿yciem funkcji)
\param [in] rows - ilosc wierszy w obrazie wejœciowym i wyjœciowym
\param [in] cols - ilosc wierszy w obrazie wejœciowym i wyjœciowym
\param [in] kerneltype - wybór j¹dra dla opercji erozji: 0 - prostok¹t, 1 - krzy¿, 2 - elipsa
\param [in] kernelsize - wielkoœæ j¹dra: = 2*kernsize + 1, nie wiêcej ni¿ 21
\return zwraca wynik dzia³ania funkcji: 0 - oznacza poprawne zakoñczenie, >0 oznacza odpowiedni b³¹d
\author LM
*/
UINT16 CV_erosion(UINT16* inp, UINT16* out, UINT16 rows, UINT16 cols, int kerneltype, int kernelsize)
{
	if (kerneltype > 2 || kernelsize > 21) return 1;
	try
	{
		Mat image = Mat(rows, cols, CV_8UC3, inp).clone();
		Mat new_image;
		
		int erosion_type;
		if (kerneltype == 0){ erosion_type = MORPH_RECT; }
		else if (kerneltype == 1){ erosion_type = MORPH_CROSS; }
		else if (kerneltype == 2) { erosion_type = MORPH_ELLIPSE; }

		int erosion_size = kernelsize;

		Mat element = getStructuringElement(erosion_type, Size(2 * erosion_size + 1, 2 * erosion_size + 1), Point(erosion_size, erosion_size));

		/// Apply the erosion operation
		erode(image, new_image, element);
		
		new_image.convertTo(new_image, CV_8UC3);
		memcpy(out, new_image.data, new_image.total() * new_image.elemSize());
		

	} // od try
	catch (Exception &e)
	{
		std::string tekst1 = e.what();
		return 1;
	}

	return 0;

}

/** @function CV_dilation
\brief funkcja s³u¿y do wykonania operacji dylatacji
\param [in] inp - wskaŸnik na obraz wejœciowy (musi byæ zarezerwowany przed u¿yciem funkcji)
\param [out] out - wskaŸnik na obraz wyjœciowy (musi byæ zarezerwowany przed u¿yciem funkcji)
\param [in] rows - ilosc wierszy w obrazie wejœciowym i wyjœciowym
\param [in] cols - ilosc wierszy w obrazie wejœciowym i wyjœciowym
\param [in] kerneltype - wybór j¹dra dla opercji dylatacji: 0 - prostok¹t, 1 - krzy¿, 2 - elipsa
\param [in] kernelsize - wielkoœæ j¹dra: = 2*kernsize + 1, nie wiêcej ni¿ 21
\return zwraca wynik dzia³ania funkcji: 0 - oznacza poprawne zakoñczenie, >0 oznacza odpowiedni b³¹d
\author LM
*/
UINT16 CV_dilation(UINT16* inp, UINT16* out, UINT16 rows, UINT16 cols, int kerneltype, int kernelsize)
{
	if (kerneltype > 2 || kernelsize > 21) return 1;
	try
	{
		Mat image = Mat(rows, cols, CV_8UC3, inp).clone();
		Mat new_image;
				
		int dilation_type;
		if (kerneltype == 0){ dilation_type = MORPH_RECT; }
		else if (kerneltype == 1){ dilation_type = MORPH_CROSS; }
		else if (kerneltype == 2) { dilation_type = MORPH_ELLIPSE; }

		int dilation_size = kernelsize;

		Mat element = getStructuringElement(dilation_type,	Size(2 * dilation_size + 1, 2 * dilation_size + 1),	Point(dilation_size, dilation_size));
		/// Apply the dilation operation
		dilate(image, new_image, element);

		new_image.convertTo(new_image, CV_8UC3);
		memcpy(out, new_image.data, new_image.total() * new_image.elemSize());


	} // od try
	catch (Exception &e)
	{
		std::string tekst1 = e.what();
		return 1;
	}

	return 0;

}


/** @function CV_smooth
\brief funkcja s³u¿y do wykonania operacji wyg³adzenia (rozmycia)
\param [in] inp - wskaŸnik na obraz wejœciowy (musi byæ zarezerwowany przed u¿yciem funkcji)
\param [out] out - wskaŸnik na obraz wyjœciowy (musi byæ zarezerwowany przed u¿yciem funkcji)
\param [in] rows - ilosc wierszy w obrazie wejœciowym i wyjœciowym
\param [in] cols - ilosc wierszy w obrazie wejœciowym i wyjœciowym
\param [in] type - typ rozmycia: 0 - jednorodny, 1 - Gaussa, 2 - medianowy, 3 - dwustronny (bilateralny)
\param [in] kernellength - d³ugoœæ j¹dra
\return zwraca wynik dzia³ania funkcji: 0 - oznacza poprawne zakoñczenie, >0 oznacza odpowiedni b³¹d
\author LM
*/
UINT16 CV_smooth(UINT16* inp, UINT16* out, UINT16 rows, UINT16 cols, int type, int kernellength)
{
	int MAX_KERNEL_LENGTH = 31;
	if (type > 3 || kernellength > MAX_KERNEL_LENGTH) return 1;
	try
	{
		Mat image = Mat(rows, cols, CV_8UC3, inp).clone();
		Mat new_image = image.clone();

		if (type == 0)
		{
			//rozmycie jednorodne Homogeneous blur
			blur(image, new_image, Size(kernellength, kernellength), Point(-1, -1));
		}
		else if (type == 1)
		{
			//rozmycie Gaussa Gaussian blur
			GaussianBlur(image, new_image, Size(kernellength, kernellength), 0, 0);
		}
		else if (type == 2)
		{
			//rozmycie medianowe Median blur
			medianBlur(image, new_image, kernellength);
		}
		else if (type == 3)
		{
			//filtr dwustronny Bilateral Filter
			bilateralFilter(image, new_image, kernellength, kernellength * 2, kernellength / 2);
		}

		new_image.convertTo(new_image, CV_8UC3);
		memcpy(out, new_image.data, new_image.total() * new_image.elemSize());


	} // od try
	catch (Exception &e)
	{
		std::string tekst1 = e.what();
		return 1;
	}

	return 0;


}