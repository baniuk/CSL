/**
* \file    LV_FastMedian.cpp
* \brief	Implementation of Fast Median based on ISAR project
* \details Exports the following functions:
* - LV_MedFilt  - Filtering using any mask
* \author  PB
* \date    2012/09/08
* \version 1.0 Initial version based on ISAR project
*/

#include "LV_FastMedian/LV_FastMedian.h"
#include <crtdbg.h>
#include <vector>
#include <algorithm>

#ifndef SAFE_DELETE
#define SAFE_DELETE(p)       { if(p) { delete[] (p);     (p)=nullptr; } }
#endif

/**
* \brief Zwraca wartość z tablicy na pozycji [r,k], przy załozeniu że tablica jest interpretowana jako 2D
* \param[in] image		struktura opisująca obraz
* \param[in] r			rząd
* \param[in] k			kolumna
* \return wartość na pozycji tab[r,k]
* \remarks W obrazie dane układane sa rzedami, zgodnie z C_MatrixContainer
*/
inline unsigned short getPoint(OBRAZ *image, unsigned int r, unsigned int k)
{
	_ASSERT(r*image->cols+k<image->tabsize);
	return image->tab[r*image->cols+k];
}

/**
* \brief Zwraca medianę z wektora wartości
* \param[in] tab		tablica wartości
* \param[in] tabsize		rozmiar tablicy
* \return wartość mediany
*/
unsigned short getMedian(const unsigned short *tab, unsigned int tabsize)
{
	std::vector<unsigned int> v( tab, tab+tabsize );
	std::nth_element( v.begin(), v.begin()+tabsize/2,v.end() );
	return v[tabsize/2];
}

/**
* \brief Kopiuje okno o rozmiarze 2*halfmedian+1 z obrazka wejściowego do tablicy out.
* \details Kopiuje rzędami jak na obrazie oryginalnym dodatkowo tworzy histogram
* \param[in] input_image		obraz wejściowy
* \param[in] mask				nieparzysty rozmiar maski
* \param[in] current_row		indeks rzędu dla którego wyciąć okno - indeks w którym jest środek okna
* \param[in] current_col		indeks kolumny dla której wyciąć okno - indeks w którym jest środek okna
* \param[out] out				tablica wyjściowa o rozmiarze maski
* \param[out] hist				tablica z histogramem okna
* \remarks Funkcja czyści tablicę hist. Jeśli okno wystaje poza obszar obrazu to wpisywane są 0 do okna
* \todo Tą funkcję można przyspieszyć używając kopiowania całych rzędów !!
*/
void CopyWindow( OBRAZ *input_image,
				unsigned short mask,
				unsigned int current_row,
				unsigned int current_col,
				unsigned short *out,
				unsigned int *hist )
{
	int wr,wk;			// indeksy wewnątrz okna
	unsigned short bok_maski = (mask-1)/2;
	unsigned int l;	// licznik
	memset(hist, 0, GRAYSCALE*sizeof(unsigned int));	// szybkie zerowanie pamięci histogramu (dla kazdego rzędu procedura działa od początku)
	for (wr = static_cast<int>(current_row)-bok_maski,l=0;wr<static_cast<int>(current_row)+bok_maski+1;wr++)
		for (wk = static_cast<int>(current_col)-bok_maski;wk<static_cast<int>(current_col)+bok_maski+1;wk++)
		{
			if(wr<0 || wk<0 || wk>=static_cast<int>(input_image->cols) || wr>=static_cast<int>(input_image->rows))	// jeśli okno wystaje poza obraz to wpisywane są w to miejsce zera
				out[l] = 0;
			else
				out[l] = getPoint(input_image,wr,wk);	// kopiowanie danych z obrazu do osobnej tablicy reprezentującej okno
			hist[out[l]]++;	// obliczam histogram
			l++;
		}
}

/**
* \brief Zwraca medianę z wektora reprezentowanego przez jego histogram
* \param[in] hist		tablica z histogramem
* \param[in] tabsize		rozmiar tablicy
* \return wartość mediany
* \remarks Na podstawie http://mathematics.blurtit.com/q6132160.html
*/
unsigned short getMedianHist( const unsigned int *hist, unsigned int tabsize )
{
	unsigned int cum_hist[GRAYSCALE]; // histogram kumulacyjny
	unsigned short cum_index[GRAYSCALE];	// indeksy z histo które wchodzą w sklad kumulacyjnego (niezerowe wartości histogramu)
	unsigned short licznik;
	unsigned short a=0;
	unsigned short M;
	unsigned int prev_cum;

	while(a<GRAYSCALE-1 && 0==hist[a])	// jeśli pierwszy element histo jest 0, to szukamy pierwszego niezerowego, a sprawdzam w zakresie 0-65535 (uwaga na przepełnienie)
		a++;
	if(a==GRAYSCALE-1)	// to znaczy że w histo są same 0, kończymy, zwracając medianę
		return 0;

	// jeśli normalny histogram to wycinamy wartości niezerowe
	cum_hist[0] = hist[a];	// pierwsza wartość niezerowa
	cum_index[0] = a;	// oraz jej indeks
	licznik = 1;	// od następniej wartości bo zerowa już ustawiona powyżej
	// obliczanie kumulacyjnego ale tylko z wartości niezerowych
	for(unsigned int b=a+1;b<GRAYSCALE;b++)	// uwaga na przepełnienie - b nie może być szort
		if (hist[b]>0)
		{
			cum_hist[licznik] = cum_hist[licznik-1] + hist[b]; // niezerowa wartość
			cum_index[licznik] = b; // oraz jej index w histo (jasność piksela)
			licznik++;
		}
		--licznik;	// indeks ostatniego elementu w cum_hist i cum_indeks
		M = cum_hist[licznik]/2;
		// do którego przedziału trafia M?
		for(a=0;a<=licznik;a++)
			if(M<cum_hist[a])
				break;
		if(0==a)	// czyli należy do pierwszego przedziału
			prev_cum = 0;
		else
			prev_cum = cum_hist[a-1];

		// mediana
		return cum_index[a] + (M-prev_cum)/hist[ cum_index[a] ];
}

/**
* \brief Filtruje obraz medianą
* \details Na podstawie Huang, A Fast Two-Dimensional Median Filtering Algorithm.
* \param[in] image		obraz wejściowy
* \param[out] tabout	wskaźnik na tablice wyjściową z przefiltrowanym obrazem o rozmiarze obrazu wejściowego
* \param[in] mask		rozmiar maski, maska nieparzysta i kwadratowa
* \remarks Na rogach obrazu pojawiają się zera. Pozatym można procedurę jeszcze przyspieszyć modyfikując pierwszą medianę (może na containerze będzie szybsza (getMedian)
* oraz modyfikując pobieranie wartości okna poprzez kopiowanie całych rzedów na raz (są liniowo w pamięci).
* \todo Add progress feature
* \todo Add error_codes support
*/
void FastMedian_Huang(	OBRAZ *image,
					  unsigned short *tabout,
					  unsigned short mask)
{
	unsigned int *hist = nullptr;				// histogram obszaru filtrowanego
	unsigned short *window = nullptr;			// dane z okna maski
	unsigned short mdm;						// wartość mediany w oknie
	unsigned int lmdm;					// liczba elementów obrazu o wartościach mniejszych od mdm
	unsigned short *left_column = nullptr;		// lewa kolumna okna
	unsigned short *right_column = nullptr;	// prawa kolumna okna
	unsigned int r,k;						// indeksy bierzącej pozycji okna na obrazie (środka)
	unsigned short mask_center = (mask+1)/2;// środek maski (indeks)
	unsigned short bok_maski = (mask-1)/2;	// rozmiar boku maski cała maska to 2*bok + 1
	unsigned int l;							// licznik
	unsigned short picval;					// pomocnicza wartość piksela obrazu
	unsigned int th = (mask*mask)/2;			// parametr pomocniczy

	hist = new unsigned int[GRAYSCALE];		// zakładam głębię 16 bit
	left_column = new unsigned short[mask];	// lewa kolumna poprzedniej pozycji maski (maska jest zawsze kwadratowa)
	right_column = new unsigned short[mask];// prawa kolumna bierzacej maski
	window = new unsigned short[static_cast<unsigned int>(mask)*mask];
	/*
	* Przeglądanie obrazu po rzędach a procedura szybkiej filtracji po
	* kolumnach. Dla kazdego nowego rzędu powtarza się wszystko od początku.
	*/
	for (r = 0;r<image->rows;r++)	// główna pętla po rzędach obrazu
	{
		// -------------------- inicjalizacja parametrów dla każdego rzędu --------------------------
		k = 0;
		CopyWindow(image,mask,r,k,window,hist);	// kopiowanie okna skrajnego lewego dla danego rzędu
		// 		mdm = getMedian(window,static_cast<unsigned int>(mask)*mask);	// znajduję medianę z okna
		mdm = getMedianHist(hist,GRAYSCALE);
		tabout[r*image->cols+k] = mdm;	// ustawiam wyjście przy założeniu że tabout jaest taka sama jak tabin
		// obliczanie lmdm
		for(l=0,lmdm=0;l<static_cast<unsigned int>(mask)*mask;l++)
			if(window[l]<mdm)
				lmdm++;
		for (k = 0+1;k<image->cols;k++)	// główna pętla po kolumnach obrazu, dla pierwszej pozycji k=mask_center obliczane jest osobno
		{
			// modyfikacja histogramu - Na podstawie Huang, A Fast Two-Dimensional Median Filtering Algorithm

			CopyOneColumn(image,mask,static_cast<int>(r)-bok_maski,static_cast<int>(k)-bok_maski-1,left_column); //pobieranie lewej kolumny poprzedniego (k-1) okna (podaję [r,k] początku kolumny
			CopyOneColumn(image,mask,static_cast<int>(r)-bok_maski,static_cast<int>(k)+bok_maski,right_column);	// prawa kolumna bierzącego k okna
			// liczenie mediany
			for(l=0;l<mask;l++)	// po wszystkich wartościach kolumny
			{
				picval = left_column[l];
				_ASSERT(hist[picval]>0);	// jeśli =0 to po odjęciu przepełnienie
				hist[ picval ]--;	// kasowanie lewej kolumny z histogtramu
				if (picval<mdm)
					lmdm--;
				picval = right_column[l];
				_ASSERT(hist[picval]<65535);	// jeśli =65535 to po odjęciu przepełnienie
				hist[picval]++;		// dodawanie prawej kolummny
				if (picval<mdm)
					lmdm++;
			}	// koniec pętli po kolumnach okna
			if (lmdm>th)
				while (lmdm>th)	// zmiana względem oryginału !!! FUCK !!
				{
					_ASSERT(mdm>0);
					mdm--;
					_ASSERT(lmdm>=hist[mdm]);
					lmdm-=hist[mdm];
				}
			else
				while(lmdm+hist[mdm]<=th)
				{
					lmdm+=hist[mdm];
					_ASSERT(mdm<65535);
					mdm++;
				}

				tabout[r*image->cols+k] = mdm;	// ustawiam wyjście przy założeniu że tabout jaest taka sama jak tabin
		} // koniec pętli po kolumnach obrazu
	} // koniec pętli po rzędach

	SAFE_DELETE(hist);
	SAFE_DELETE(left_column);
	SAFE_DELETE(right_column);
	SAFE_DELETE(window);
}

/**
* \brief kopiuje jedną kolumnę zaczynając od pozycji poz
* \details Na podstawie Huang, A Fast Two-Dimensional Median Filtering Algorithm
* \param[in] input_image		obraz wejściowy
* \param[in] mask		rozmiar maski, maska nieparzysta i kwadratowa
* \param[in] r			rząd startowy
* \param[in] k			kolumna startowa
* \param[out] out		tablica o rozmiarze mask z kolumną
* \remarks Procedura dopuszcza ujemne kolumny i rzędy, co odpowiada sytuacji gdy kolumna nie miesci się
* na obrazie, czyli dla berzegów
*/
void CopyOneColumn( OBRAZ *input_image, unsigned short mask, int r, int k, unsigned short *out )
{
	unsigned short a;
	for (a=0;a<mask;a++)
	{
		if(r<0 || r>=static_cast<int>(input_image->rows) || k<0 || k>=static_cast<int>(input_image->cols))	// jeśli rząd lub kolumna poza obrazem t owpisywane są 0
			out[a] = 0;
		else
			out[a] = getPoint(input_image,r,k);
		r++;
	}
}

/**
* \brief Performs median filtering of input image
* \details Assumes that input image is 1D array. Any positive and non-zero mask can be used. Returns filtered copy of
* input image (the same size)
* \param[in] input_image 1D input image
* \param[out] output_image	pointer to array of size of input image
* \param[in] nrows	number of rows (height) of input/output image
* \param[in] ncols number of cols (width) of input/output image
* \param[in] mask filter mask uneven and nonzero
* \param[out] errDesc Error description
* \return operation status, LV_OK on success, LV_FAIL on:
* \li mask is 0
* \li mask is negative
* \retval retCode
* \remarks Returned image has the same size as input image
*/
extern "C" __declspec(dllexport) retCode LV_MedFilt(const UINT16* input_image,
													UINT16* output_image,
													UINT16 nrows, UINT16 ncols,
													UINT16 mask,
													char* errDesc)
{
	_ASSERT(input_image);
	_ASSERT(output_image);
	if(0==mask)
		return setError::throwError("FastMedian::Maska równa 0",&errDesc);
	if(mask<0)
		return setError::throwError("FastMedian::Maska mniejsza od 0",&errDesc);
	if( mask%2 == 0)
		return setError::throwError("Maska parzysta", &errDesc);
	OBRAZ obraz;	// lokalna kopia obrazu wejściowego (płytka)
	obraz.tab = input_image;
	obraz.rows = nrows;
	obraz.cols = ncols;
	obraz.tabsize = nrows*ncols;
	FastMedian_Huang(&obraz,output_image,mask);
	return retCode::LV_OK;
}