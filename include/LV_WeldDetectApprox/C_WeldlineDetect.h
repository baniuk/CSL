/**
* \file    C_WeldlineDetect.h
* \brief	Klasa abstrakcyjna obsłogująca wykrywanie linii spawu
* \author  PB
* \date    2012/03/01
*/

#ifndef C_WeldlineDetect_h__
#define C_WeldlineDetect_h__

#include <vector>
#include <algorithm>
#include <iostream>
//#include "C_Matrix_Container.h"
#include "C_CircBuff.h"
#include "C_LineWeldApprox.h"
#include "C_LineInterp.h"
#include "C_WeldPos.h"
#include "definitions.h" // for UINT16 CASELOT

/**
* \brief Simple struct for compatibility with C_MatrixContiner
* \details The aim of this struct is to replace old C_MatrixContained class for easier compatibility with CASELOT
*/
struct Matrix_Container
{
	const double* data; ///< image data in rows
	unsigned int _rows; ///< number of rows
	unsigned int _cols; ///< number of columns
};

using namespace std;
/**
* Klasa abstrakcyjna implementująca metody używane do wykrywania linii spawu. Z tej klasy dziedziczone będą klasy do spawów liniowych i zakrzywionych. Wektory lineOK oraz WeldPos są zsynchronizowane, dana pozycja dotyczy okreslonej linii. Dane w WeldPos są ważne tylko jesli w lineOK jest status OK na tej pozycji. Te dwa wektory obejmują wszystkie linie spawu - łącznie z tymi niepoprawnymi. Dostęp do nich poprzez funkcje getLineOK() oraz getweldPos().\n
* W celu przyspieszenie procedury podczas wypełniania bufora od razu przeliczane są wyniki aproxymacji i wstawiane do bufora recalculated_approx_data. Ten bufor idzie w parze z dobrymi liniami. Jest używany do wyznaczenia wag w procedurze evalNextParams(). Podczas obliczeń dane są przechowywane w 3 buforach - są to obiekty interpolacji->aproxymacji->oraz przeliczone dane na podstawie obiektu aproxymacji. W buforach są tylko dobre linie, tzn takie które mają mały błąd aproxyamcji. Zrezygnowano z przechowywania przeliczonych dnych w obiekcie aproxymacji aby zaoszczędzić pamięć. W każdej chwili można te dane jednak obliczyć:
* \code
double *evaldata = new double[_interp->getSizeofInterpData()]; // tablica na dane obliczone dla krzywej aproxymacyjnej
const double *x,*y;	// wskazniki na wektory x i y dla których została wykonan interpolacja i aproxymacja (współrzędne obrazu)
x = _interp->getInterpolated_X();
y = _interp->getInterpolated_Y();
_approx->evalApproxFcnVec(y,evaldata,_interp->getSizeofInterpData());
*	\endcode
*	\remarks
*	Generalnie jedną para zbierznych buforów jest lineOK oraz weldPos - te bufory obejmują wszystkie linie obrazka dla których jest liczona aproxymacja. Drugim zestawe są wymienione wcześniej bufory kołowe, które także sa zgodne.\n
*	Rozmiar danch tez ma znaczneie przy innych spawach niz liniowe. Trzeba pilnowac zeby zawsze tyle smo punktów było\n
*/
class C_WeldlineDetect
{
	friend class C_LinearWeld_Test1;
	friend class C_LinearWeld_Test2;
	friend class C_LinearWeld_FillBuffor;
public:
	/// pobiera obrazek rtg
	C_WeldlineDetect(const Matrix_Container *_rtg);
	virtual ~C_WeldlineDetect();
	/// ustawia parametry procedury i tworzy potrzebne struktury
	virtual void SetProcedureParameters(unsigned int _k, C_Point _StartPoint)=0;
	/// Znajduje profil spawu
	virtual bool Start(unsigned int step,unsigned int ile)=0;
	/// zwraca wyniki detekcji spawu
	const vector<bool> *getLineOK() const { return lineOK; }
	/// zwraca wyniki detekcji spawu
	const vector<C_WeldPos> *getweldPos() const { return weldPos; }
	/// oblicza aprxymacje jednej linii
	virtual bool getOneApproxLine(C_WeldPos &weldpos)=0;
protected:
	/// przechowuje wskaźnik do obrazka
	const Matrix_Container *rtg;
	/// generuje zestaw paramstrów do detekcji kolejnej linii - punkty P0 i P1
	virtual bool evalNextStartPoint(unsigned int step)=0;
	/// generuje zestaw kolejnych parametrów aproxymacji oraz wagi
	virtual bool evalNextParams()=0;
	/// wypełnia bufory approxymując k poczatkowych linii
	virtual bool fillBuffor()=0;
	/// przechowuje k poprzednich wyników aproxymacji
	C_CircBuff<C_LineWeldApprox> *approx_results;
	/// przechowuje k ostatnich wyników interpolacji linii - dane do aproxymacji i generowania wag
	C_CircBuff<C_LineInterp> *interp_lines;
	/// Bufor pomocniczy przechowujący przeliczone wartości funkcji aproxymującej - ma na celu przyspieszenie
	C_CircBuff<double> *recalculated_approx_data;
	/** Przechowuje inforację czy linia jest poprawna czy nie - poprawność określona na podstwie czyAccept. Jesli linia jest poprawna to jest OK a jeśli nie to BLAD*/
	vector<bool> *lineOK;
	/// ilość poprzendich wyników brana pod uwagę
	unsigned int k;
	/// rozmiar obrazka wejściowego potrzebny do funkcji interpolującej
	unsigned int rtgsize[3];
	double *_w; /**< Tablica wag. Jest inicjalizowana jednorazowo w funkcji evalNextParams*/
	/// tablica przechowującej obiekty C_WeldPos
	vector<C_WeldPos> *weldPos;
	/// funkcja sprawdza czy obliczona aproksymacja może byćzaakcepyowana czy nie
	virtual bool czyAccept(const C_LineWeldApprox *_approx, const C_LineInterp *_interp) = 0;
	/// funkcja oblicza pozycjespawu dla danej linii
	virtual void evalWeldPos(const C_LineWeldApprox *_approx, const C_LineInterp *_interp, const double *_pre, C_WeldPos &_weldPos )=0;
	/// funkcja oblicza pozycjespawu dla danej linii
	virtual void evalWeldPos(const C_LineWeldApprox *_approx, const C_LineInterp *_interp, C_WeldPos &_weldPos )=0;
};
#endif // C_WeldlineDetect_h__