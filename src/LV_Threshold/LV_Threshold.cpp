/**
* \file    LV_Threshold.cpp
* \brief	Implementation of Savuola thresholding
* \details Contains static functions for testing purposes. Exported methods are in DLL_Wrapper
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
* \retval \c void
* \author PB
* \date 2014/10/10
* \warning Obraz wyjściowy musi być rozmiaru obrazu wejściowego
*/
void Sauv( const UINT16* input, UINT16* output, unsigned int rows, unsigned int cols )
{
	_ASSERT(output);	// obraz wyjściowy alokowany na zewnątrz

	std::size_t nEl = rows*cols;	// liczba elementów macierzy
	UINT16 max, min;				// wartości min max dla macierzy wejściowej
	double R;

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

	// call SAUVOLA

	delete[] owe2;
	delete[] II;
	delete[] II2;
}


/*****************************************************************************************
Program: Implementacja progowania Sauvola z wykorzystaniem wieloątkowości
Autor: Lech Napierała
Parametry wejściowe:
	owe - obraz w odcieniach szarości do sprogowania
	w - rozmiar okna progowania (koniecznie nieparzysty!)
	k - parametr 'k' progowania (standardowa wartość to 0.2)
Parametry wyjściowe:
	owy - obraz dwukolorowy po progowaniu
Wersja: 1.0
*****************************************************************************************/
/*
#pragma once
#include "mex.h"
#include "C_Matrix_Container.h"
#include "C_Image_Container.h"
#include "C_Error.h"
#include <process.h>
#include <stdio.h>

#define N 400	//maksymalna liczba procesorów

/*  założenie jest takie aby własciwa procedura była umieszczona w osobnej funkcji,
	dzięki czemu będzie ją można później łatwo przetransporotowac do innego programu.
	Funkcja ta musi pobierać i zwracać dane w formacie już klas C_Matrix itp
	(oczywiście jeśli jest taka potrzeba) */



//	moja funkcja - dodaje dwie macierze do siebie (in1+in2) i zwraca wynik out
void Sauv(C_Image_Container* owe, double w, double k, double n, C_Image_Container* owy, C_Error* perr);
//bool Add(C_Matrix_Container* in1,C_Matrix_Container* in2, C_Matrix_Container* out);

//	moja funkcja - dodaje dwie macierze do siebie (in1+in2) i zwraca wynik out. Oczywiście jest 
// i wskaźnik do C_Error
//void Add(C_Matrix_Container* in1,C_Matrix_Container* in2, C_Matrix_Container* out, C_Error* perr);

void mexFunction(int nlhs, mxArray *plhs[], int nrhs,
                 const mxArray *prhs[])
{

	double *p_in1, *p_out;//, *p_in2;			// wskaźniki na dane w formacie matlaba
	//int a;
	double *pN, *w, *k;//, *xx, *yy;		//Zmienne do przechowywania parametrów z matlaba
	//double N = 2, w = 15, k = 0.2;
	//bool err;
	C_Image_Container in1;			// wejscie do funkcji
	C_Image_Container out;// = new C_Image_Container;
	//C_Image_Container in2;			// wejscie do funkcji
	//C_Matrix_Container out;		// wyjście z funkcji
	C_Error errr;				// obsługa błędów

//	żeby nie komplikować nie sprawdzam poprawnosci danych - zakładam że w matlabie bedzie wszystko dobrze wywołane
//	Najwyżej można dorobić jakiegoś m-file który to będzie robił. W funkcji własciwej i tak trzeba to zaimplementować
//  żeby uniknąć problemów gdy będzie ona pracować w innym środowisku
	
	p_in1 = mxGetPr(prhs[0]);
	//xx = mxGetPr(prhs[1]);
	//yy = mxGetPr(prhs[2]);
	
	w = mxGetPr(prhs[1]);
	k = mxGetPr(prhs[2]);
	pN = mxGetPr(prhs[3]);
	
	//p_in2 = mxGetPr(prhs[1]);

	plhs[0] = mxCreateDoubleMatrix(mxGetM(prhs[0]),mxGetN(prhs[0]), mxREAL);	// to jest macierz wyjściowa w formacie matlaba o rozmiarze pierwszego parametru
	p_out = mxGetPr(plhs[0]);							// tu jej wskaźnik

//	konwersja danych z matlaba na postać akceptowalna przez moją funkcję
	in1.ImportFromMatlab(p_in1,mxGetM(prhs[0]),mxGetN(prhs[0]));	// importowanie danych z matlaba
	//in2.ImportFromMatlab(p_in2,mxGetM(prhs[1]),mxGetN(prhs[1]));	// importowanie danych z matlaba

	Sauv(&in1, *w, *k, *pN, &out, &errr);	// wywołanie funkcji
	//Sauv(&in1, w, k, N, &out, &errr);	// wywołanie funkcji
	//Add(&in1,&in2,&out,&errr);	// wywołanie funkcji
	if(errr.status)		// obsługa błędu zgłoszonego przez moją funkcję
	{
		mexPrintf("%s\n",errr.error);
		return;
	}
//	konwersja danych z mojej funkcji do matlaba
	out.ExportToMatlab(p_out);
}





//Struktury do przekazywania danych wątkom:
struct CIC
{
	C_Image_Container *o1;
	C_Image_Container *o2;
} cic[2];

struct SAV
{
	int imin, imax;
	int jmin, jmax;
	int w;
	double k;
	double R;
	C_Image_Container *owe;
	C_Image_Container *owy;
	C_Image_Container *II;
	C_Image_Container *II2;
} sav[N];

//Compute Integral Image - liczy Integral Image z tego co dostanie na wejściu
//z obrwe robimy integrala i zapisujemy w obrwy
unsigned int WINAPI CII(void* param)
{
	struct CIC *c;

	c = (struct CIC *)param;

	C_Image_Container *obrwe = c->o1;
	C_Image_Container *obrwy = c->o2;

	int i, j;

	for(i = 1; i < obrwe->_cols; i++) 
	{
		obrwy->data[i] = obrwe->data[i] + obrwy->data[i - 1]; //2
	}
	for(i = 1; i < obrwe->_rows; i++) //3
	{
		obrwy->data[i * obrwe->_cols] = obrwe->data[i * obrwe->_cols] + obrwy->data[(i - 1) * obrwe->_cols];
	}
		
	for(i = 1; i < obrwe->_rows; i++) //4
	{
		for(j = 1; j < obrwe->_cols; j++)
		{
			obrwy->data[i * (obrwe->_cols) + j] =
				obrwy->data[(i - 1) * obrwe->_cols + j] + obrwy->data[i * obrwe->_cols + j - 1] - 
				obrwy->data[(i - 1) * obrwe->_cols + j - 1] + obrwe->data[i * obrwe->_cols + j];
		}
	}
	return 0;
}

unsigned int WINAPI SAUVOLA(void* param)
{
	struct SAV *s;
	s = (struct SAV *)param;

	int i, j, imin, imax, jmin, jmax, fW, w;
	double k, R;
	double wspW, wspW2, srednia, suma1, odSt, t;
	C_Image_Container *II, *II2, *owe, *owy;
	unsigned long w2;
	imin = s->imin;
	imax = s->imax;
	jmin = s->jmin;
	jmax = s->jmax;
	w = s->w;
	k = s->k;
	R = s->R;
	II = s->II;
	II2 = s->II2;
	owe = s->owe;
	owy = s->owy;
	wspW = 1 / pow(w, 2.0);
	wspW2 = 1 / (pow(w, 2.0) - 1);
	w2 = pow(w, 2.0);
	fW = int(w / 2.0);

	for(i = imin; i <= imax; i++)
	{
		for(j = jmin; j <= jmax; j++)
		{


			srednia = 
				(II->data[(i + fW) * owe->_cols + j + fW] +
				II->data[(i - fW - 1) * owe->_cols + j - fW - 1] -
				II->data[(i - fW - 1) * owe->_cols + j + fW] -
				II->data[(i + fW) * owe->_cols + j - fW - 1]) *
				wspW;

			
			suma1 =
				II2->data[(i + fW) * owe->_cols + j + fW] +
				II2->data[(i - fW - 1) * owe->_cols + j - fW - 1] -
				II2->data[(i - fW - 1) * owe->_cols + j + fW] -
				II2->data[(i + fW) * owe->_cols + j - fW - 1];

		

			odSt = sqrt(wspW2 * (suma1 - w2 * pow(srednia, 2)));
			t = srednia * (1 + k * ((odSt / R) - 1));

			
			
			if(owe->data[i * (owe->_cols) + j] > t)
				owy->data[i * (owe->_cols) + j] = 1;
			
			
		}
	}
	return(0);
}


void Sauv(C_Image_Container* owe, double w, double k, double n, C_Image_Container* owy, C_Error* perr)
{
	C_Image_Container *owe2 = new C_Image_Container;//obraz wejściowy do kwadratu
	C_Image_Container *II = new C_Image_Container;  //Integral image
	C_Image_Container *II2 = new C_Image_Container; //Integral image kwadratów
	
	int i, j = 0, r, d, g, pom;		//większość do wyznacznia przedziałów
	double R;
	bool xlonger = false;
	double max, min;

	w = (int)w;

	//owy = new C_Image_Container();
	

	//Zmienne do wątków
	HANDLE hThread[N];
	owy->AllocateData(owe->_rows, owe->_cols);
	owy->Zeros();
	owe2->AllocateData(owe->_rows, owe->_cols);
	II->AllocateData(owe->_rows, owe->_cols);
	II->Zeros();
	II2->AllocateData(owe->_rows, owe->_cols);
	II2->Zeros();

	owe->getMinMax(min, max);
	R = ((max - min) / 2.0);

	//Wyliczanie owe2 (kwadraty wejścia)
	for(i = 0; i < (owe->_cols * owe->_rows); i++)
	{
		owe2->data[i] = pow(owe->data[i], 2);
	}
	
	//Liczenie Integral Images na wątkach:
	cic[0].o1 = owe2;
	cic[0].o2 = II2;
	cic[1].o1 = owe;
	cic[1].o2 = II;
	hThread[0] = (HANDLE)_beginthreadex(NULL, 0, CII, (void*)&cic[0], 0, NULL);
	hThread[1] = (HANDLE)_beginthreadex(NULL, 0, CII, (void*)&cic[1], 0, NULL);
	//CII(NULL);
	//WaitForSingleObject(hThread[0], INFINITE);
	//WaitForSingleObject(hThread[1], INFINITE);
	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);
	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);
	//DZIAŁA!!!!! : )))


	//LICZENIE SAMEGO PROGOWANIA SAUVOLA NA WĄTKACH:


	//Podział obrazu
	if(w < owe->_cols && w < owe->_rows) //Sprawdzamy czy obraz jest większy od maski, inaczej dalsze liczenie nie ma sensu
	{
		if(owe->_cols - w < n || owe->_rows - w < n) n = 1;
		if(owe->_cols > owe->_rows) 
		{
			pom = owe->_cols - w;
			xlonger = true;
		}
		else
		{
			pom = owe->_rows - w;
			xlonger = false;
		}
		if(n <= 0) n = 1;
		d = (int)(pom / n);
		r = pom % (int)n;
		for(i = 0; i < n; i++)
 		{
	 		g = j + d - 1;
			  
			if(r > 0)
			{
				r--;
				g++;
			}
			if(xlonger)
			{
				sav[i].imin = (int)(w / 2.0) + 1;
				sav[i].imax = owe->_rows - (int)(w / 2.0) - 1;
				sav[i].jmin = j + (int)(w / 2.0);
				sav[i].jmax = g + (int)(w / 2.0);
			}
			else
			{
				sav[i].imin = j + (int)(w / 2.0) + 1;
				sav[i].imax = g + (int)(w / 2.0) + 1;
				sav[i].jmin = (int)(w / 2.0) + 2;
				sav[i].jmax = owe->_cols - (int)(w / 2.0);
			}
			sav[i].w = (int)w;
			sav[i].k = k;
			sav[i].R = R;
			sav[i].II = II;
			sav[i].II2 = II2;
			sav[i].owe = owe;
			sav[i].owy = owy;
	        
			j = g + 1;
		}
		sav[0].imin = (int)(w / 2.0) + 1;
		sav[0].jmin = (int)(w / 2.0) + 1;

		
		for(i = 0; i < n; i++)
		{
			hThread[i] = (HANDLE)_beginthreadex(NULL, 0, SAUVOLA, (void*)&sav[i], 0, NULL);
		}
		
		WaitForMultipleObjects(n, hThread, TRUE, INFINITE);
		
		for(i = 0; i < n; i++)
		{
			CloseHandle(hThread[i]);
		}
	}
	//owy->CloneObject(out);
	SAFE_DELETE(owe2);
	SAFE_DELETE(II);
	SAFE_DELETE(II2);
}*/