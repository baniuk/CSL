// dll_rulproj.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "dll_rulproj.h"
#include "rulinter.hpp"
#include "C_Error.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

/*! \file dll_rulproj.cpp
    \brief Plik z funkcjami wykorzystuj¹cymi klasê RulInter do klasyfikacji wad i udostêpniaj¹cy funkcje w bibliotece dll_rulproj.dll
	\details Dostêpne s¹ nastêpuj¹ce funkcje:<br/>
	int generuj_klasy(double *dane,long rows,long cols,int *wynik)<br/>
	Funkcja klasyfikuj¹ca wady (wykorzystuje klasê RulInter) z wejœcia bêd¹cego jednowymiarow¹ tablic¹ (dwuwymiarowa tablica zapisana w jednym wymiarze)<br/>
	int generuj_klasy_plik(char *nazwa,int *wynik)<br/>
	Funkcja klasyfikuj¹ca wady (wykorzystuje klasê RulInter) z wejœcia bêd¹cego plikiem o okreœlonej strukturze<br/><br/>
	\author LM
*/


// *dane - tablica z danymi wejœciowymi
// rows - iloœæ wierszy w tanlicy wejœciowej
// cols - iloœæ kolumn w tablicy wejœciowej
// *wynik - jednowymiarowa tablica z wynikiem przydzielnania do klas
// wynik - 0 - dobrze, >0 - odpowiedni numer b³êdu

/** @function generuj_klasy
	\brief Funkcja klasyfikuj¹ca wady (wykorzystuje klasê RulInter) z wejœcia bêd¹cego jednowymiarow¹ tablic¹ (dwuwymiarowa tablica zapisana w jednym wymiarze)
	\param [in] dane - wskaŸnik na jednowymiarow¹ tablicê z danymi do klasyfikacji (jest to dwuwymiarowy element zapisane w jednym wymiarze)
	\param [in] rows - iloœæ wierszy w danych wejœciowych (parametr dane)
	\param [in] cols - iloœæ kolumn w danych wejœciowych (parametr dane)
	\param [out] wynik - wskaŸnik na tablicê do zapisania wyników klasyfikacji wad (musi byæ zaalokowany na zewn¹trz)
	\return zwraca 0 - w przypadku powodzenia, inne wartoœci w przypadku b³êdów
	\author LM
*/
int generuj_klasy(double *dane,long rows,long cols,int *wynik)
{
  C_Error error;
  RulInter *obj = new RulInter(4); //inicjujemy obiekt, parametr 4 - reguly momentowe, 1 - reguly niemomentowe
  obj->configuration(); //konfiguracja przypisania rzeczywistego parametru wady  do indeksu dane[]
  obj->RSS(dane, rows, cols, wynik, &error); //obliczenie klas, wejscie: dane, rows, cols   wyjscie: wynik = przypiana klasa w tablicy
  delete obj;
//tutaj koniec kodu do wywolania 

  return 0;
}



/** @function generuj_klasy_plik
	\brief Funkcja klasyfikuj¹ca wady (wykorzystuje klasê RulInter) z wejœcia bêd¹cego plikiem o okreœlonej strukturze
	\param [in] nazwa - plik wejœciowy o okreœlonej strukturze z parametrami wad 
	\param [out] wynik - wskaŸnik na tablicê do zapisania wyników klasyfikacji wad (musi byæ zaalokowany na zewn¹trz)
	\return zwraca 0 - w przypadku powodzenia, inne wartoœci w przypadku b³êdów
	\author LM
*/
int generuj_klasy_plik(char *nazwa,int *wynik)
{
  C_Error error;
  RulInter *obj = new RulInter(4); //inicjujemy obiekt, parametr 4 - reguly momentowe, 1 - reguly niemomentowe
  obj->configuration(); //konfiguracja przypisania rzeczywistego parametru wady  do indeksu dane[]
  obj->loadFile(nazwa); //ladowanie danych z pliku
  obj->induct(wynik,2); //obliczenie klas, wejscie: dane z pliku   wyjscie: wynik = przypiana klasa w tablicy
  delete obj;
  return 0;
}


//
//TODO: If this DLL is dynamically linked against the MFC DLLs,
//		any functions exported from this DLL which call into
//		MFC must have the AFX_MANAGE_STATE macro added at the
//		very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

// Cdll_rulprojApp

BEGIN_MESSAGE_MAP(Cdll_rulprojApp, CWinApp)
END_MESSAGE_MAP()


// Cdll_rulprojApp construction

Cdll_rulprojApp::Cdll_rulprojApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only Cdll_rulprojApp object

Cdll_rulprojApp theApp;


// Cdll_rulprojApp initialization

BOOL Cdll_rulprojApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}
