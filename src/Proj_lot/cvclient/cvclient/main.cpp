/*! \file main.cpp
\brief Klient, kt�ry wykorzystuje bibliotek� cvlib.dll do cel�w testowych dla funkcji, kt�re znajduj� si� w bibliotece cvlib.dll
\details Opis szczecg�owy u�ycia (po komplikacji do cvclient.exe):<br/>
cvclient.exe <operacja> <nazwa_pliku_graficznego><br/>
Rodzaje dla opcji operacja:<br/><br/>
jasnosc<br/>
konturowanie<br/>
morfologia<br/>
zalewanie<br/>
erozja<br/>
dylatacja<br/>
wygladzanie<br/><br/>

Przyk�ad dla operacji konturowania:<br/>
cvclient.exe konturowanie 02.tif<br/><br/>
\author LM
\see cvprocess.cpp
*/


//#include "stdafx.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/types_c.h"
#include "opencv2/core/core_c.h"
#include <opencv2/core/core.hpp>
#include <vector> 

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "examples.h"
#include <windows.h>
//#include <atlstr.h>
//#include <strsafe.h>

using namespace std;
using namespace cv;

typedef UINT16 (*CV_brightness)(UINT16* inp, UINT16* out, UINT16 rows, UINT16 cols, double alpha, int beta);
typedef UINT16(*CV_convolve)(UINT16* inp, UINT16* out, UINT16 rows, UINT16 cols, int kerneltype);
typedef UINT16 (*CV_morphpology)(UINT16* inp, UINT16* out, UINT16 rows, UINT16 cols, int operation, int kerneltype, int kernsize);
typedef UINT16 (*CV_watershed)(UINT16* inp, UINT16* out, UINT16 rows, UINT16 cols);
typedef UINT16 (*CV_erosion)(UINT16* inp, UINT16* out, UINT16 rows, UINT16 cols, int kerneltype, int kernelsize);
typedef UINT16 (*CV_dilation)(UINT16* inp, UINT16* out, UINT16 rows, UINT16 cols, int kerneltype, int kernelsize);
typedef UINT16 (*CV_smooth)(UINT16* inp, UINT16* out, UINT16 rows, UINT16 cols, int type, int kernellength);


/** @function brightness
\brief funkcja s�u�y do testowania funkcji CV_brightness do zmiany wielko�ci jasno�ci oraz kontrastu
\param [in] argv - plik wej�ciowy
\param [in] alpha - parametr zmiennoprzecinkowy okre�laj�cy poziom kontrastu
\param [in] beta - parametr sta�oprzecinkowy okre�laj�cy poziom jasno�ci
\author LM
*/
void brightness(char** argv, double alpha, int beta)
{
	Mat src = imread(argv[2]); // Read the file
	UINT16 powrot;
	if (src.empty()) { cout << "Bledny plik graficzny.\n"; return; }

	byte *dst = new byte[src.total() * src.elemSize()];
	HINSTANCE hDLL;               // Handle to DLL
	CV_brightness Func1;    // Function pointer

	hDLL = LoadLibraryW((LPCWSTR)L"cvlib.dll");
	if (hDLL == NULL)
	{
		std::cout << "BLAD LADOWANIA biblioteki DLL cvlib.dll";
		return;
	}
	else
	{
		Func1 = (CV_brightness)GetProcAddress(hDLL, "CV_brightness");
		if (!Func1)
		{
			std::cout << "BLAD LADOWANIA FUNKCJI CV_brightness z biblioteki DLL cvlib.dll";
			FreeLibrary(hDLL);
			return;
			
		}
		else
		{
			DWORD dw1 = GetTickCount();
			powrot = Func1((UINT16*)src.data, (UINT16*)dst, src.rows, src.cols, alpha, beta);
			DWORD dw2 = GetTickCount();
			cout << "Time difference is " << (dw2 - dw1) << " milliSeconds" << endl;
		}

	}

	if (powrot == 0)
	{
		imshow("Obraz oryginalny", src);
		Mat wynik = Mat(src.rows, src.cols, CV_8UC3, dst).clone();
		imshow("Zmiana kontratu i jasnosci", wynik);
	}
	else
	{
		std::cerr << "B��d wykonania funkcji CV_brightness.";
	}
	 
	 FreeLibrary(hDLL);
}

/** @function convolve
\brief funkcja s�u�y do testowania funkcji CV_convolve do tak zwanej operacji konturowania (ang.convolve)
\param [in] argv - plik wej�ciowy
\param[in] kerneltype - typ j�dra 1 - j�dro 3x3 wymiarowe: warto�ci -1 �rodek 11, typ j�dra 2 - j�dro 5x5 wymiarowe: warto�ci -1 �rodek 29
\author LM
*/
void convolve(char** argv, int kerneltype)
{
	Mat src = imread(argv[2]); // Read the file
	UINT16 powrot;
	if (src.empty()) { cout << "Bledny plik graficzny.\n"; return; }

	byte *dst = new byte[src.total() * src.elemSize()];
	HINSTANCE hDLL;               // Handle to DLL
	CV_convolve Func1;    // Function pointer

	hDLL = LoadLibraryW((LPCWSTR)L"cvlib.dll");
	if (hDLL == NULL)
	{
		std::cout << "BLAD LADOWANIA biblioteki DLL cvlib.dll";
		return;
	}
	else
	{
		Func1 = (CV_convolve)GetProcAddress(hDLL, "CV_convolve");
		if (!Func1)
		{
			std::cout << "BLAD LADOWANIA FUNKCJI CV_convolve z biblioteki DLL cvlib.dll";
			FreeLibrary(hDLL);
			return;

		}
		else
		{
			DWORD dw1 = GetTickCount();
			powrot = Func1((UINT16*)src.data, (UINT16*)dst, src.rows, src.cols, kerneltype);
			DWORD dw2 = GetTickCount();
			cout << "Time difference is " << (dw2 - dw1) << " milliSeconds" << endl;
		}

	}

	if (powrot == 0)
	{
	imshow("Obraz oryginalny", src);
	Mat wynik = Mat(src.rows, src.cols, CV_8UC3, dst).clone();
	imshow("Konturowania", wynik);
    }
	else
	{
		std::cerr << "B��d wykonania funkcji CV_convolve.";
	}
	
	FreeLibrary(hDLL);
}

/** @function morphpology
\brief  funkcja s�u�y do testowania funkcji CV_morphpology do operacji morfologicznych takich jak: otwarcie, zamkni�cie, gradient, operacja tzw. "Top Hat", operacja tzw. "Black Hat"
\param [in] argv - plik wej�ciowy
\param [in] operation - operacja morfologiczna: 0 - otwarcie, 1 - zamkni�cie, 2 - gradient, 3 - operacja tzw. "Top Hat", 4 - operacja tzw. "Black Hat"
\param [in] kerneltype - wyb�r j�dra dla opercji morfologicznej: 0 - prostok�t, 1 - krzy�, 2 - elipsa
\param [in] kernelsize - wielko�� j�dra: = 2*kernsize + 1, nie wi�cej ni� 21
\author LM
*/
void morphpology(char** argv, int operation, int kerneltype, int kernsize)
{
	Mat src = imread(argv[2]); // Read the file
	UINT16 powrot;
	if (src.empty()) { cout << "Bledny plik graficzny.\n"; return; }

	byte *dst = new byte[src.total() * src.elemSize()];
	HINSTANCE hDLL;               // Handle to DLL
	CV_morphpology Func1;    // Function pointer

	hDLL = LoadLibraryW((LPCWSTR)L"cvlib.dll");
	if (hDLL == NULL)
	{
		std::cout << "BLAD LADOWANIA biblioteki DLL cvlib.dll";
		return;
	}
	else
	{
		Func1 = (CV_morphpology)GetProcAddress(hDLL, "CV_morphpology");
		if (!Func1)
		{
			std::cout << "BLAD LADOWANIA FUNKCJI CV_morphpology z biblioteki DLL cvlib.dll";
			FreeLibrary(hDLL);
			return;

		}
		else
		{
			DWORD dw1 = GetTickCount();
			powrot = Func1((UINT16*)src.data, (UINT16*)dst, src.rows, src.cols, operation, kerneltype, kernsize);
			DWORD dw2 = GetTickCount();
			cout << "Time difference is " << (dw2 - dw1) << " milliSeconds" << endl;
		}

	}

	if (powrot == 0)
	{
		imshow("Obraz oryginalny", src);
		Mat wynik = Mat(src.rows, src.cols, CV_8UC3, dst).clone();
		imshow("Wybrana operacja morfologiczna", wynik);
	}
	else
	{
		std::cerr << "B��d wykonania funkcji CV_morphpology.";
	}

	FreeLibrary(hDLL);
}

/** @function watershed
\brief  funkcja s�u�y do testowania funkcji CV_watershed do operacji segmentacji tzw. rozlewowej (ang. watershed)
\param [in] argv - plik wej�ciowy
\author LM
*/
void watershed(char** argv)
{
	Mat src = imread(argv[2]); // Read the file
	UINT16 powrot;
	if (src.empty()) { cout << "Bledny plik graficzny.\n"; return; }

	byte *dst = new byte[src.total() * src.elemSize()];
	HINSTANCE hDLL;               // Handle to DLL
	CV_watershed Func1;    // Function pointer

	hDLL = LoadLibraryW((LPCWSTR)L"cvlib.dll");
	if (hDLL == NULL)
	{
		std::cout << "BLAD LADOWANIA biblioteki DLL cvlib.dll";
		return;
	}
	else
	{
		Func1 = (CV_watershed)GetProcAddress(hDLL, "CV_watershed");
		if (!Func1)
		{
			std::cout << "BLAD LADOWANIA FUNKCJI CV_watershed z biblioteki DLL cvlib.dll";
			FreeLibrary(hDLL);
			return;

		}
		else
		{
			DWORD dw1 = GetTickCount();
			powrot = Func1((UINT16*)src.data, (UINT16*)dst, src.rows, src.cols);
			DWORD dw2 = GetTickCount();
			cout << "Time difference is " << (dw2 - dw1) << " milliSeconds" << endl;
		}

	}

	if (powrot == 0)
	{
		imshow("Obraz oryginalny", src);
		Mat wynik = Mat(src.rows, src.cols, CV_8UC3, dst).clone();
		imshow("Wynik operacji segmentacji rozlewowej", wynik);
	}
	else
	{
		std::cerr << "B��d wykonania funkcji CV_watershed.";
	}

	FreeLibrary(hDLL);
}

/** @function erosion
\brief  funkcja s�u�y do testowania funkcji CV_erosion do wykonania operacji erozji
\param [in] argv - plik wej�ciowy
\param [in] kerneltype - wyb�r j�dra dla opercji erozji: 0 - prostok�t, 1 - krzy�, 2 - elipsa
\param [in] kernelsize - wielko�� j�dra: = 2*kernsize + 1, nie wi�cej ni� 21
\author LM
*/
void erosion(char** argv,int kerneltype, int kernelsize)
{
	Mat src = imread(argv[2]); // Read the file
	UINT16 powrot;
	if (src.empty()) { cout << "Bledny plik graficzny.\n"; return; }

	byte *dst = new byte[src.total() * src.elemSize()];
	HINSTANCE hDLL;               // Handle to DLL
	CV_erosion Func1;    // Function pointer

	hDLL = LoadLibraryW((LPCWSTR)L"cvlib.dll");
	if (hDLL == NULL)
	{
		std::cout << "BLAD LADOWANIA biblioteki DLL cvlib.dll";
		return;
	}
	else
	{
		Func1 = (CV_erosion)GetProcAddress(hDLL, "CV_erosion");
		if (!Func1)
		{
			std::cout << "BLAD LADOWANIA FUNKCJI CV_erosion z biblioteki DLL cvlib.dll";
			FreeLibrary(hDLL);
			return;

		}
		else
		{
			DWORD dw1 = GetTickCount();
			powrot = Func1((UINT16*)src.data, (UINT16*)dst, src.rows, src.cols, kerneltype, kernelsize);
			DWORD dw2 = GetTickCount();
			cout << "Time difference is " << (dw2 - dw1) << " milliSeconds" << endl;
		}

	}

	if (powrot == 0)
	{
		imshow("Obraz oryginalny", src);
		Mat wynik = Mat(src.rows, src.cols, CV_8UC3, dst).clone();
		imshow("Wynik operacji erozji", wynik);
	}
	else
	{
		std::cerr << "B��d wykonania funkcji CV_erosion.";
	}

	FreeLibrary(hDLL);
}

/** @function dilation
\brief  funkcja s�u�y do testowania funkcji CV_dilation do wykonania operacji dylatacji
\param [in] argv - plik wej�ciowy
\param [in] kerneltype - wyb�r j�dra dla opercji dylatacji: 0 - prostok�t, 1 - krzy�, 2 - elipsa
\param [in] kernelsize - wielko�� j�dra: = 2*kernsize + 1, nie wi�cej ni� 21
\author LM
*/
void dilation(char** argv, int kerneltype, int kernelsize)
{
	Mat src = imread(argv[2]); // Read the file
	UINT16 powrot;
	if (src.empty()) { cout << "Bledny plik graficzny.\n"; return; }

	byte *dst = new byte[src.total() * src.elemSize()];
	HINSTANCE hDLL;               // Handle to DLL
	CV_dilation Func1;    // Function pointer

	hDLL = LoadLibraryW((LPCWSTR)L"cvlib.dll");
	if (hDLL == NULL)
	{
		std::cout << "BLAD LADOWANIA biblioteki DLL cvlib.dll";
		return;
	}
	else
	{
		Func1 = (CV_dilation)GetProcAddress(hDLL, "CV_dilation");
		if (!Func1)
		{
			std::cout << "BLAD LADOWANIA FUNKCJI CV_dilation z biblioteki DLL cvlib.dll";
			FreeLibrary(hDLL);
			return;

		}
		else
		{
			DWORD dw1 = GetTickCount();
			powrot = Func1((UINT16*)src.data, (UINT16*)dst, src.rows, src.cols, kerneltype, kernelsize);
			DWORD dw2 = GetTickCount();
			cout << "Time difference is " << (dw2 - dw1) << " milliSeconds" << endl;
		}

	}

	if (powrot == 0)
	{
		imshow("Obraz oryginalny", src);
		Mat wynik = Mat(src.rows, src.cols, CV_8UC3, dst).clone();
		imshow("Wynik operacji dylatacji", wynik);
	}
	else
	{
		std::cerr << "B��d wykonania funkcji CV_dilation.";
	}

	FreeLibrary(hDLL);
}

/** @function smooth
\brief  funkcja s�u�y do testowania funkcji CV_smooth do operacji wyg�adzenia (rozmycia)
\param [in] argv - plik wej�ciowy
\param [in] type - typ rozmycia: 0 - jednorodny, 1 - Gaussa, 2 - medianowy, 3 - dwustronny (bilateralny)
\param [in] kernelnength - d�ugo�� j�dra
\author LM
*/
void smooth(char** argv, int type, int kernellength)
{
	Mat src = imread(argv[2]); // Read the file
	UINT16 powrot;
	if (src.empty()) { cout << "Bledny plik graficzny.\n"; return; }

	byte *dst = new byte[src.total() * src.elemSize()];
	HINSTANCE hDLL;               // Handle to DLL
	CV_dilation Func1;    // Function pointer

	hDLL = LoadLibraryW((LPCWSTR)L"cvlib.dll");
	if (hDLL == NULL)
	{
		std::cout << "BLAD LADOWANIA biblioteki DLL cvlib.dll";
		return;
	}
	else
	{
		Func1 = (CV_smooth)GetProcAddress(hDLL, "CV_smooth");
		if (!Func1)
		{
			std::cout << "BLAD LADOWANIA FUNKCJI CV_smooth z biblioteki DLL cvlib.dll";
			FreeLibrary(hDLL);
			return;

		}
		else
		{
			DWORD dw1 = GetTickCount();
			powrot = Func1((UINT16*)src.data, (UINT16*)dst, src.rows, src.cols, type, kernellength);
			DWORD dw2 = GetTickCount();
			cout << "Time difference is " << (dw2 - dw1) << " milliSeconds" << endl;
		}

	}

	if (powrot == 0)
	{
		imshow("Obraz oryginalny", src);
		Mat wynik = Mat(src.rows, src.cols, CV_8UC3, dst).clone();
		imshow("Wynik operacji wyg�adzania", wynik);
	}
	else
	{
		std::cerr << "B��d wykonania funkcji CV_smooth.";
	}

	FreeLibrary(hDLL);
}

void wywolanie(char **argv)
{
	cout << "Program do testowania podsawowych operacji\n";
	cout << argv[0] << " operacja nazwa_pliku_graficznego\n";
	cout << "Rodzaje dla opcji operacja:\n";
	cout << "jasnosc\n";
	cout << "konturowanie\n";
	cout << "morfologia\n";
	cout << "zalewanie\n";
	cout << "erozja\n";
	cout << "dylatacja\n";
	cout << "wygladzanie\n\n";
	cout << "Przyk�ad dla operacji konturowania : \n";
	cout << "cvclient.exe konturowanie 02.tif \n\n";

}

void test_funkcji(int argc, char **argv)
{
	if (argc < 3)
	{
		wywolanie(argv);
		return;
	}
	if (strcmp(argv[1], "jasnosc") == 0)
	{
		// u�ycie funkcji CV_brightness
		brightness(argv, 2.0, 40);
	}
	else if (strcmp(argv[1], "konturowanie") == 0)
	{
		// operacja konturowania za pomoc� funkcji CV_convolve
		convolve(argv, 1);
	}
	else if (strcmp(argv[1], "morfologia") == 0)
	{
		//operacja morfologiczna za pomoc� funkcji CV_morphpology
		morphpology(argv, 0, 0, 14);
	}
	else if (strcmp(argv[1], "zalewanie") == 0)
	{
		//operacja segmentacji rozlewowej za pomoc� funkcji CV_watershed
		watershed(argv);
	}
	else if (strcmp(argv[1], "erozja") == 0)
	{
		//operacja erozji za pomoc� funkcji CV_erosion
		erosion(argv, 0, 7);
	}
	else if (strcmp(argv[1], "dylatacja") == 0)
	{
		//operacja dylatacji za pomoc� funkcji CV_dilation
		dilation(argv, 0, 7);
	}
	else if (strcmp(argv[1], "wygladzanie") == 0)
	{
		//operacja wyg�adzania za pomoc� funkcji CV_smooth
		smooth(argv, 0, 7);
	}
	else
		wywolanie(argv);

}


int main(int argc, char** argv)
{

	//detekcja t�a grabcut
	//detekcja_grabcut();

	//funkcja normalizacji kolor�w
	//norm_color();
	
	// funkcja Leszek u�ycie biblioteki
	//return mainold(argc, argv);

	// przyk�ad u�ycia BackgroundSubtractorMOG oraz BackgroundSubtractorMOG2 dla animacji lub serii obraz�w
	//return main_background(argc, argv);

	// przyk�ad segmentacji obrazu OTSU
	//watershed1();

	// przyk�ad segmentacji obrazu OTSU + usuniecie szumow + otwarcie + dylatacja + t�o
	//watershed2();

	// algorytm wykrywania tla - wcze�niejsza wersja opencv
	//tlo();

	//regulacja jasno�ci oraz kontrastu
	//return main_jasnosc(argc, argv);

	// dyskretna transformata fouriera
	//return main_fourier(argc, argv);

	// watershed1
	//return main_watershed1(argc, argv);

	//demonstracja threshold
	//return main_threshold(argc, argv);

	//funkcje morfologiczne
	//return main_morphology(argc, argv);

    // funkcja erozji oraz dylatacji
	//return main_erozja(argc, argv);

	// kontury obrazow
	//return main_kontury(argc, argv);

	// wygladzanie
	//return main_smooth(argc, argv);

	// moja konwulsja
	//convolvelm(argv);

	//algorytm watershed2
	//return main_watershed2(argc, argv);

	// watershed_2a
	//return main_watershed2a(argc, argv);

	//wykorzystanie funkcji z biblioteki cvprocess.cpp
	// u�ycie funkcji CV_brightness
	//brightness(argv, 2.0, 40);

	// operacja konturowania za pomoc� funkcji CV_convolve
	//convolve(argv, 1);

	//operacja morfologiczna za pomoc� funkcji CV_morphpology
	//morphpology(argv, 0, 0, 14);

	//operacja segmentacji rozlewowej za pomoc� funkcji CV_watershed
	//watershed(argv);

	//operacja erozji za pomoc� funkcji CV_erosion
	//erosion(argv, 0, 7);

	
	//operacja dylatacji za pomoc� funkcji CV_dilation
	//dilation(argv, 0, 7);

	//operacja wyg�adzania za pomoc� funkcji CV_smooth
	//smooth(argv, 3, 27);

	
	test_funkcji(argc, argv);
		
	cv::waitKey();
	return 0;
}
