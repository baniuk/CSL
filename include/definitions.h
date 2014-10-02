/**
* \file    definitions.h
* \brief   Zawiera definicje podstwowych typów danych
* \details Powinien być dołączony do wszystkich projektów a także wykorzystany pod LabView aby
* zapewnić spójność
* \author  PB
* \date    2014/10/02
*/

#ifndef definitions_h__
#define definitions_h__

/**
* Definiuje możliwe wartości zwracane przez każdą funkcję w DLL
* \todo Zastanowić się nad sensem <b>enum classes</b> c C++11
*/
enum retCode
{
	LV_OK = 0,	///< Brak błędu
	LV_FAIL		///< Błąd generalny
};

// definicje innych stałych
#define MAX_ERROR_STRING 256	///< Maksymalna długość opisu błedu razem ze znakiem końca \0

// definicje typów danych zgodnych z LV
typedef unsigned short UINT16;	///< 2 bajty bez znaku, opisuje piksel obrazu

#endif // definitions_h__