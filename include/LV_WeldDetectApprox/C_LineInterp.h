/**
* \file    C_LineInterp.h
* \brief	Interpoluje profil liniowy obrazy zdjęty z linii prostej.
* \author  PB
* \date    2012/03/01
*/
#ifndef C_LineInterp_h__
#define C_LineInterp_h__

#ifndef SAFE_DELETE
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#endif

#include <memory.h>
#include <crtdbg.h>
#include "Geom/C_Line.h"
#include "LV_WeldDetectApprox/interpol.h"
#include "LV_WeldDetectApprox/coeff.h"

/// Rodzaje approxymacji
enum APPROX_TYPE {
	SPLINE
};
/**
* Klasa realizujaca interpolację danych na obrazie na podstawie linii pomiędzy punktami. Przechowuje kopię danych
* ze względu na wymóg float stawiany przez procedury interpolacji. Przy inicjalizacji trzeba podać odnoścnik do obrazu oraz macierzy 3
* elementowej określającej ilość elementów w każdym wymiarze.
* Interpolowane dane oraz ich współrzędne są przechowywane wewnętrz klasy i dostępne za pomocą C_LineApprox::getInterpolated_data.
* Schmemat działania:\n
* \li Inicjalizacja obiektu = dane interpolowane interpolated_data ustawione na null oraz image też - jeśli użyty jest domyślny konstruktor to trzeba inicjalizować funkcją manualConstructor()
* \li Interpolacja getPointsOnLine wypełnione są tablice oraz zwracane współrzędne x,y punktów dla których wykonana była interpolacja
* \li Pobranie wyników za pomocą funkcji read-only getInterpolated_data oraz getInterpolatedXY
*/
class C_LineInterp : public C_Line
{
public:
	/// domyślny konstruktor
	C_LineInterp();
	/// konstruktor wykorzystujący współczynniki prostej
	C_LineInterp(APPROX_TYPE type,const double &_a, const double &_b, const KIERUNEK_PROSTEJ &_czy_pion, const double *const _image, const unsigned int _size[] );
	/// konstruktor wykorzystujący punkty przez które prosta przechodzi
	C_LineInterp(APPROX_TYPE type,const C_Point &_P0, const C_Point &_P1, const double *const _image, const unsigned int _size[] );
	/// definiuje linie interpolacji na podstawie 2 punktów
	virtual void ManualConstructor(APPROX_TYPE type,const C_Point &P0, const C_Point &P1, const double *const _image, const unsigned int _size[] );
	/// Wykonuje interpolację Zapisuje obliczone punkty w obiekcie
	virtual bool getPointsOnLine( const C_Point &_P0, const C_Point &_P1, unsigned int _Np, float** image  );
	/// zwaraca ilość elementów na podstawie tablicy im_size
	unsigned int getNumOfElements() const;
	/// zwraca tablicę z interpolowanymi danymi
	const double * getInterpolated_data() const { return interpolated_data; }
	/// zwraca tablice ze współrzędnymi x
	const double * getInterpolated_X() const { return x; }
	/// zwraca tablice ze współrzędnymi y
	const double * getInterpolated_Y() const { return y; }
	/// zwraca rozmiar danych w tablicach x, y, interpolated_data
	unsigned int getSizeofInterpData() const { return Np; }
	virtual ~C_LineInterp();
protected:
	//	void Interpolate
private:
	/// Tworzy tablice w klasie
	void SafeAllocateTab();
	/// kopiuje dane pomiędzy buforami
	inline void DataCopy(double *src,double *dest);
	APPROX_TYPE typ_interpolacji;
	/// wskaźnik przechowujący obraz, jest modyfikowany przez getPointsOnLine
	float *image;
	/// tablica przechowująca wynik interpolacji dla punktów [x y]
	double *interpolated_data;
	/// wymiary danych w image [rows cols z]
	unsigned int im_size[3];
	/// ilosc elementów obrazu
	unsigned int N;
	/// ilość elementów w interpolowanym wektorze interpolated_dataoraz x i y
	unsigned int Np;
	/// tablica z wsp x - zawiera współrzędne x punktów dla których wykonano interpolacje
	double *x;
	/// tablica z wsp y - zawiera współrzędne y punktów dla których wykonano interpolacje
	double *y;
	/// wskaźnik rzechowuje oryginalny obraz
	const double *rtg;
};

#endif // C_LineApprox_h__
