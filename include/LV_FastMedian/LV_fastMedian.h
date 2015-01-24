/**
* \file    LV_fastMedian.h
* \brief	Headers and definitions for LV_FastMedian.dll
* \author  PB
* \date    2012/09/08
*/

#ifndef fastMedian_h__
#define fastMedian_h__

#include "definitions.h"
#include <inttypes.h>
/**
* \struct OBRAZ
* \brief Struktura opisująca obraz lub bardziej generalnie obszar pamięci
* \remarks Stosowana lokalnie w LV_FastMedian
*/
struct OBRAZ
{
	const unsigned short *tab; /** wskażnik na tablicę z obrazem */
	unsigned int rows; /** ilość rzędów */
	unsigned int cols; /** ilość kolumn */
	unsigned int tabsize;	/** ilość elementów tablicy = rows*cols */
};

/// Filtruje obraz medianą
void FastMedian_Huang(	OBRAZ *image,
					  unsigned short *tabout,
					  unsigned short mask);

/// Dokonuje konwersji z pozycji [x,y] do liniowej
inline unsigned short getPoint(OBRAZ *image, int r, int k);
/// Zwraca medianę z wektora
unsigned short getMedian(const unsigned short *tab, unsigned int tabsize);
/// Zwraca medianę z histogramu
unsigned short getMedianHist(const unsigned int *hist, unsigned int tabsize);
/// Kopiuje kwadratową maskę z obrazu liniowego
void CopyWindow(OBRAZ *input_image,
				unsigned short mask,
				unsigned int current_row,
				unsigned int current_col,
				unsigned short *out,
				unsigned int *hist);
/// Kopiuje jedną kolumnę obrazu
void CopyOneColumn( OBRAZ *input_image, unsigned short mask, int r, int k, unsigned short *out );
/// Number of gray levels in the image
#define GRAYSCALE 65536

#endif // fastMedian_h__
