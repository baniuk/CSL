/**
* \file setError.cpp
* \brief Implementacja klasy setError
* \author PB
* \date 2014/10/02
*/

#include "setError/setError.h"

/**
* \brief Zwraca sformatowany łańcuch błedu o okreslonej długości
* \details Automatycznie kontroluje długość łańcucha opisującego błąd aby nie dopuœcić do przekroczenia pamięci
* przydzielonej w LV na ten łańcuch. Za długi komunikat jest przycinany bez zwracania jakiejkolwiek informacji o
* przekroczeniu dozwolonej długoœci \c MAX_ERROR_STRING
* \param[in] _errorDesc - lańcuch z opisem błędu
* \param[out] _formattedErrorDesc - sformatowany (skrócony) łańcuch \c _errorDesc
* \return kod błędu \c LV_FAIL
* \retval retCode
* \author PB
* \date 2014/10/02
* \see definitions.h
*/
retCode setError::throwError(const char* _errorDesc, char** _formattedErrorDesc)
{
	std::string errDesc(_errorDesc);	// c++ string copy of const char* string
	if (errDesc.length() > MAX_ERROR_STRING-1)	// jeœli za d³ugi to tniemy (+ miejsce na \0)
		errDesc.resize(MAX_ERROR_STRING-1);
	// kopiowanie skróconego ³añcucha do pamiêci LV
	std::strcpy(*_formattedErrorDesc, errDesc.c_str());	// errDesc na pewno jest krótszy niż MAX_ERROR_STRING
	return retCode::LV_FAIL;
}
/** \example setError_example.cpp
* Przykład użycia klasy setError to zwrócenia błedu w funkcji DLL-a
*/