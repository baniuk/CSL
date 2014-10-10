/**
* \file setError.h
* \brief Definicja klasy setError
* \author PB
* \date 2014/10/02
*/

#ifndef setError_h__
#define setError_h__

#include <string>
#include <cstring>
#include "definitions.h"

/**
* \class setError
* \brief Prosta klasa pomocnicza obsługująca zwracanie błędów do LV
* \details W związku z tym ze pamięć na opis błedu allokowana jest po stronie LabView i ma ona stałą i niezmienną
* wielkość określoną przez stałą MAX_ERROR_STRING istnieje niebezpieczeństwo przekroczenia tej pamięci przy
* zwracaniu komunikatu z błedem. Rolą tej klasy jest ograniczenie długości zwracanego łańcucha. Ze względu na lokalny
* charakter błedu nie ma potrzeby czynienia go "obiektem". Wystarczy jedna metoda statyczna
* \remarks Obsługa błędow w LV przebiega dwudrożnie - każda metoda zwraca przez wartość \c LV_OK albo \c LV_FAIL oraz
* dodatkowo kopiuje pod adres <b>char*</b> \c error_desc opis błędu. Parametr formalny \c error_desc jest obligatoryjnym
* parametrem każdej funkcji.
* \author PB
* \date 2014/02/05
* \see definitions.h
* \see setError_example.cpp
*/
class setError
{
public:
	/// Zwraca sformatowany łańcuch błedu o okreslonej długości
	static retCode throwError(const char* _errorDesc, char** _formattedErrorDesc);
private:
	setError(void) {};
	~setError(void) {};
};
#endif // setError_h__