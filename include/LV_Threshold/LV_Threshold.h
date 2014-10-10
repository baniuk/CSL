/**
* \file    LV_Threshold.h
* \brief	Headers and definitions for LV_Threshold.dll
* \author  PB
* \date    2014/10/10
*/

#ifndef threshold_h__
#define threshold_h__

#include "setError/setError.h"
#include "definitions.h"
#include <memory>

typedef unsigned int UINT32; 	///< 4 bajty bez znaku, opisuje kwadrat piksela obrazu

/**
* \struct SAV
* \brief Struktura do przekazywania danych do metody SAUVOLA
* \details Całkowicie na podstawie Leszka aby zachować kompatybilność
* \author PB
* \date 2014/10/10
*/
struct SAV
{
	unsigned int imin, imax;
	unsigned int jmin, jmax;
	int w;
	double k;
	double R;
	UINT16* owe;
	UINT16* owy;
	UINT32* II;
	UINT32* II2;
} sav;

/// Compute Integral Image - liczy Integral Image
void CII(const UINT32* input, UINT32* output, unsigned int rows, unsigned int cols);
/// Wykonuje przygotowania do progowania Sauvola
void Sauv(const UINT16* input, UINT16* output, unsigned int rows, unsigned int cols, unsigned int w, double k);
/// Progowanie
void SAUVOLA(SAV& s);

/**
* \brief Czyści pamięć, wupełniając ją zerami
* \param[in] mem wskaźnik do czyszczonej pamięci
* \param[in] siz rozmiar pamięci
* \retval \c void
* \author PB
* \date 2014/10/10
*/
template<typename T>
inline void clearMem(T* mem, std::size_t siz)
{
	for(std::size_t i = 0; i < siz; ++i)
		mem[i] = 0;
}

/**
* \brief  Zwraca wartość minimalną i maksymlaną
* \param[in] input macierz wejściowa
* \param[in] siz liczba elementów macierzy \c input
* \param[out] _min wartość minimalna w macierzy \c input
* \param[out] _max wartość maksymlana w macierzy \c input
* \retval \c void
* \author PB
* \date 2014/10/10
* \todo Przenieść do PBToolset
*/
template<typename T>
void getMinMax(const T* input, std::size_t siz, T& _min, T& _max)
{
	std::size_t i;
	_min = input[0];
	_max = input[0];
	for(i = 0; i < siz; i++)	{
		if(input[i] < _min) _min = input[i];
		if(input[i] > _max) _max = input[i];
	}
}

/**
* \brief Oblicza Integral Image
* \details Na podstawie kodu Leszka. Macierz \c output allokowana poza metodą
* \param[in] input macierz wejściowa
* \param[out] output macierz wyjściowa
* \param[in] rows liczba wierszy macierzy
* \param[in] cols liczba kolumn macierzy
* \retval \c void
* \author PB
* \date 2014/10/10
* \warning Macierz wejściowa i wyjściowa ma taki sam rozmiar
* \warning Macierz \c output musi być wyzerowana
*/
template<typename T>
void CII( const T* input, UINT32* output, unsigned int rows, unsigned int cols )
{
	_ASSERT(output);	// jeśli nie ma pamięci zaalokowanej
	std::size_t i,j;
	for(i = 1; i < cols; i++)
	{
		output[i] = input[i] + output[i - 1]; //2
	}
	for(i = 1; i < rows; i++) //3
	{
		output[i * cols] = input[i * cols] + output[(i - 1) * cols];
	}

	for(i = 1; i < rows; i++) //4
		for(j = 1; j < cols; j++)
		{
			output[i * (cols) + j] =
				output[(i - 1) * cols + j] + output[i * cols + j - 1] -
				output[(i - 1) * cols + j - 1] + input[i * cols + j];
		}
}
#endif // threshold_h__
