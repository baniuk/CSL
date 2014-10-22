/**
* \file    C_LinearWeld.h
* \brief	Implementuje dekecje spawów liniowych
* \author  PB
* \date    2012/03/01
*/
#ifndef C_LinearWeld_h__
#define C_LinearWeld_h__

#include "C_WeldlineDetect.h"

/// maksymalny błąd aproxymacji który jest akceptowany. Powyżej tego błędu dane są odrzucane
#define MAX_ERROR_LEVEL 90000
/// ile rpocent wysokości spawu to brzeg
#define WELD_EDGE 0.2

#ifndef BLAD
#define BLAD false
#endif
#ifndef OK
#define OK true
#endif

/**
* Klasa implementujaca funkcje do wykrywania spawów liniowych. W ramach obiektu tworzonego z tej klasy realizowana jest pełna procedura wykrywania. Sposób użycia w testach parametrycznych C_LinearWeld_FillBuffor case1 i inne. Podstawą jest funkcja start(), wyniki są w struktyrach weldPos oraz lineOK. W tych strukturach są wszystkie wyniki dla każdej znalezionej linii. Bufory weldPos oraz lineOK są zbierzne, to jest na odpowiednich pozycjach są odpowiadające sobie dane.
*/
class C_LinearWeld : public C_WeldlineDetect
{
	friend class C_LinearWeld_Test1;
	friend class C_LinearWeld_FillBuffor_test2;
	friend class C_LinearWeld_FillBuffor;
public:
	C_LinearWeld(const C_Matrix_Container *_rtg);
	~C_LinearWeld();
	/// Funkcja inicjalizacyjna środowiska.
	void SetProcedureParameters(unsigned int _k, C_Point _StartPoint);
	/// główna funkcja startowa
	bool Start(unsigned int step,unsigned int ile);
	/// oblicza aprxymacje jednej linii
	bool getOneApproxLine(C_WeldPos &weldpos);
protected:
	/// generuje następny punkt startowy
	bool evalNextStartPoint(unsigned int step);
	/// wypełnia bufor początkowymi aproksymacjami
	bool fillBuffor();
	/// generuje zestaw parametrów do aproksymacji izwraca je
	bool evalNextParams();
	/// sprawdza poprawność uzyskanej aproxymacji/interpolacji
	bool czyAccept(const C_LineWeldApprox *_approx, const C_LineInterp *_interp);
	/// oblicza pozycję spawu dla linii pionowej i aproxymacji gaussLin
	void evalWeldPos(const C_LineWeldApprox *_approx, const C_LineInterp *_interp,const double *_pre, C_WeldPos &_weldPos );
	/// oblicza pozycję spawu dla linii pionowej i aproxymacji gaussLin
	void evalWeldPos(const C_LineWeldApprox *_approx, const C_LineInterp *_interp, C_WeldPos &_weldPos );
private:
	/// pozycja startowa - dla spawów linowych jedynie kolumna - te punkty zmieniają się podczas działania algorytmu
	C_Point P0;
	C_Point P1;	/**< Pomiędzy P0 i P1 rozciąga się linia zdejmowania profilu */
	double _p[5]; /**< Parametry bierzące aproxymacji - także zmieniają się podczas działania algorytmu */
	double _ub[5];/**< Granice górne bierzące aproxymacji - także zmieniają się podczas działania algorytmu */
	double _lb[5];/**< Granice dolne bierzące aproxymacji - także zmieniają się podczas działania algorytmu */
};

#endif // C_LinearWeld_h__
