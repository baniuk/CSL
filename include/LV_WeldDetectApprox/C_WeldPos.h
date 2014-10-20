/**
* \file    C_WeldPos.h
* \brief	Definicja klasy przechowującej pozycję spawu dla jednej linii
* \author  PB
* \date    2012/03/17
*/
#ifndef C_WeldPos_h__
#define C_WeldPos_h__

#include "Geom/C_Point.h"
/**
* Kalsa służy doprzechowywania pozycji spawu dla jednej linii. Przechowywane są trzy punkty:
* \li Górny
* \li Środkowy
* \li Dolny\n
* Klasa musi być używana jako typ tablicowy.
*/
class C_WeldPos
{
public:
	C_Point G; /**< Punkt górny */
	C_Point S;/**< Punkt srodkowy */
	C_Point D;/**< Punkt dolny */
	/// Kasuje wszyskie pola
	void Clear();
protected:
private:
};

#endif // C_WeldPos_h__
