/**
* \file    LV_Threshold.cpp
* \brief	Implementation of Savuola thresholding
* \details Contains static functions for testing purposes. Exported methods that call this library are in DLL_Wrapper
* \author  PB
* \date    2014/10/10
* \version 1.0 Initial version based on ISAR project
*/

#include "LV_Threshold/LV_Threshold.h"
#include <crtdbg.h>

/**
* \brief Wykonuje przygotowania do progowania Sauvola
* \details Na podstawie kodu Leszka. Macierz \c output allokowana poza metodą
* \param[in] input obraz wejściowy
* \param[out] output obraz wyjściowy
* \param[in] rows liczba wierszy obrazów
* \param[in] cols liczba kolumn obrazów
* \param[in] w parametr \c w
* \param[in] k parametr \c k
* \retval \c void
* \author PB
* \date 2014/10/10
* \warning Obraz wyjściowy musi być rozmiaru obrazu wejściowego
*/
void Sauv( const UINT16* input, UINT16* output, unsigned int rows, unsigned int cols, unsigned int w, double k )
{
	_ASSERT(output);	// obraz wyjściowy alokowany na zewnątrz

	std::size_t nEl = rows*cols;	// liczba elementów macierzy
	UINT16 max, min;				// wartości min max dla macierzy wejściowej
	double R;
	unsigned int pom, g;
	bool xlonger;
	SAV sav;

	UINT32* owe2 = new UINT32[nEl]; //obraz wejściowy do kwadratu
	UINT32* II = new UINT32[nEl]; //Integral image
	clearMem<UINT32>(II, nEl);
	UINT32* II2 = new UINT32[nEl]; //Integral image kwadratów
	clearMem<UINT32>(II2, nEl);

	getMinMax<UINT16>(input, nEl, min, max);
	R = ((max - min) / 2.0);

	//Wyliczanie owe2 (kwadraty wejścia)
	for(std::size_t i = 0; i < nEl; i++)
		owe2[i] = input[i] * input[i];

	//Liczenie Integral Images
	CII<UINT32>(owe2, II2, rows, cols);
	CII<UINT16>(input, II, rows, cols);

	//Podział obrazu
	if(w < cols && w < rows) //Sprawdzamy czy obraz jest większy od maski, inaczej dalsze liczenie nie ma sensu
	{
		if(cols > rows)
		{
			pom = cols - w;
			xlonger = true;
		}
		else
		{
			pom = rows - w;
			xlonger = false;
		}
		g = pom - 1;
		if(xlonger)
		{
			sav.imin = (unsigned int)(w / 2.0) + 1;			// piksel środkowy na lewym górnym rogu - początek
			sav.imax = rows - (unsigned int)(w / 2.0) - 1;
			sav.jmin = (unsigned int)(w / 2.0);
			sav.jmax = g + (unsigned int)(w / 2.0);			// g oznacza kolumny tu (wcześniej było - cała maska)
		}
		else
		{
			sav.imin = (unsigned int)(w / 2.0) + 1;
			sav.imax = g + (unsigned int)(w / 2.0) + 1;
			sav.jmin = (unsigned int)(w / 2.0) + 2;		// ?? +2
			sav.jmax = cols - (unsigned int)(w / 2.0);
		}
		sav.w = w;
		sav.k = k;
		sav.R = R; // srednia jasność
		sav.II = II;
		sav.II2 = II2;
		sav.owe = input;
		sav.owy = output;

		sav.jmin = (unsigned int)(w / 2.0) + 1;
		sav.rows = rows;
		sav.cols = cols;
		SAUVOLA(sav);
	}

	delete[] owe2;
	delete[] II;
	delete[] II2;
}

/**
* \brief Oparta o kod Leszka
* \param[in] s struktura z parametrami
* \retval \c void
* \author PB
* \date 2014/10/11
*/
void SAUVOLA(SAV& s)
{
	unsigned int i, j, fW;
	double wspW, wspW2, srednia, suma1, odSt, t;
	unsigned long w2;
	wspW = 1 / pow(s.w, 2.0);
	wspW2 = 1 / (pow(s.w, 2.0) - 1);
	w2 = (unsigned long)pow(s.w, 2.0);
	fW = (unsigned int)(s.w / 2.0);

	for(i = s.imin; i <= s.imax; i++)
	{
		for(j = s.jmin; j <= s.jmax; j++)
		{
			srednia =
				(s.II[(i + fW) * s.cols + j + fW] +
				s.II[(i - fW - 1) * s.cols + j - fW - 1] -
				s.II[(i - fW - 1) * s.cols + j + fW] -
				s.II[(i + fW) * s.cols + j - fW - 1]) *
				wspW;

			suma1 =
				s.II2[(i + fW) * s.cols + j + fW] +
				s.II2[(i - fW - 1) * s.cols + j - fW - 1] -
				s.II2[(i - fW - 1) * s.cols + j + fW] -
				s.II2[(i + fW) * s.cols + j - fW - 1];

			odSt = sqrt(wspW2 * (suma1 - w2 * pow(srednia, 2)));
			t = srednia * (1 + s.k * ((odSt / s.R) - 1));

			if(s.owe[i * (s.cols) + j] > t)
				s.owy[i * (s.cols) + j] = 1;
		}
	}
}