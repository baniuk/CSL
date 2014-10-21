/**
* \file    C_LineWeldApprox.h
* \brief	Aproxymuje profil liniowy obrazu
* \author  PB
* \date    2012/03/01
*/
#ifndef _LineWeldApprox_H_
#define _LineWeldApprox_H_

#include "C_Levmar_Warp.h"
#include <string>
#include <time.h>

#ifndef SAFE_DELETE
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=nullptr; } }
#endif

static struct ApproxParam
{
	double p[5];
	double ub[5];
	double lb[5];
} approxParam;
/**
* Wykonuje aproxymację jednej linii spawu i przechowuje wyniki takiej aproxymacji
* Inicjalizacja następuje konstruktorem, przy przekazaniu typu krzywej aproksymujacej oraz wskaźników do wektórw
* _x oraz _y. Te wektory nie są modyfikowane wewnątrz klasy, wektor _y jest kopiowany do zmiennej pomocniczej copy_y
* co jest potrzebne przy wagach.\n
* Po inicjalizacji można wywołać funkcję C_LineWeldApprox::setApproxParams aby przekazać do klasy parmaetry aproksymacji.
* Jeśli nie wywoła się tej funkcji lub poda się NULL w argumencie to używane są parametry domyślne.\n
* Następnie wywołuje się wysokopoziomową procedurę C_LineWeldApprox::getLineApprox, która dokonuje aproksymacji i zachowuje
* wyniki w klasie. Modyfikowana jest zmienna p, która zawiera obliczone współczynniki krzywej\n
* Wyniki można uzyskać za pomocą funkcji C_LineWeldApprox::getApproxParams, która kopiuje szereg parametrów na zewnatrz klasy.
* Dodatkowe informace za pomocą funkcji C_LineWeldApprox::getInfo.
*/
class C_LineWeldApprox
{
public:
	/// Standard Constructor - po jego użyciu obowiązkowo ManualConstructor
	C_LineWeldApprox();
	/// konstruktor podstawowy
	C_LineWeldApprox(eApproxFcn _typeApprox,const double *_y, const double *_x,unsigned int _len);
	/// Destructor
	~C_LineWeldApprox();
	/// konstruktor manualny - musi być użyty po konstruktorze bezparametrowym
	void ManualConstructor(eApproxFcn _typeApprox,const double *_y, const double *_x,unsigned int _len);
	/// oblicza wartość funkcji apryxymującej dla parametru x
	//	double evalApproxFcn(double _x) const;
	/// oblicza wartość funkcji apryxymującej dla wektora x
	void evalApproxFcnVec(const double *_x,double *_y,unsigned int siz ) const;
	static void setDefaultParams();
private:
	/// wskaźnik do danych y \warning Poprzez ten wskaźnik nie można modyfikować nic
	double const *y;
	/// wskaźnik do x
	double const *x;
	/// kopia y żeby wagą nie modyfikować
	double *copy_y;
	/// przechowuje współczynniki dla funkcji GaussLin
	double *p;
	/// Przechowuje typ aproxymacji skojarzony z obiektem, zgodnie z ApproxFcn
	eApproxFcn typeApprox;
	/// Przechowuje lb
	double *lb;
	/// Przechowje ub
	double *ub;
	/// Rodzaj krzywej aproxymującej
	eApproxFcn currentApproxFcn;
	/// parametry optymalizacji
	double opts[LM_OPTS_SZ];
	/// wyniki optymalizacji
	double info[LM_INFO_SZ];
	/// Aproxymacja sumą gaussa i funkcji liniowej
	int getLineApproxGaussLinWeighted(int iter);
	/// rozmiar wektorów x i y
	unsigned int len;
	/// wazy sygnał profilu za pomocą wag
	void WeightProfile(const double *_w);
public:
	/// Aproxymuje jedną linię wybraną funkcją zgodnie z eApproxFcn
	int getLineApprox(int _iter);
	/// ustawia parametry optymalizacji i dane
	void setApproxParmas(double *_p, double *_w, double *_ub, double *_lb, double *_opts=NULL);
	/// Zwraca wybrane parametry, bez sprawdzania czy optymalizacja była wykoana
	const double* getApproxParams_p() const;
	const double* getApproxParams_ub() const;
	const double* getApproxParams_lb() const;
	/// Zwraca wybraną informację o wyniku optymalizacji
	double getInfo(eOptimInfo _res) const;
	/// Generuje pseudolosowe znaki
	void RangedRand( int range_min, int range_max, int n, char *tab );
};

#endif