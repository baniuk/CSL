/**
* \file setError.cpp
* \brief Implementacja klasy setError
* \author PB
* \date 2014/10/02
*/

#include "setError/setError.h"

/**
* \brief Zwraca sformatowany ³añcuch b³edu o okreslonej d³ugoœci
* \details Automatycznie kontroluje d³ugoœæ ³añcucha opisuj¹cego b³¹d aby nie dopuœciæ do przekroczenia pamiêci
* przydzielonej w LV na ten ³añcuch. Za d³ugi komunikat jet przycinany bez zwracania jakiejkolwiek informacji o
* przekroczeniu dozwolonej d³ugoœci \c MAX_ERROR_STRING
* \param[in] _errorDesc - lañcuch z opisem b³êdu
* \param[out] _formattedErrorDesc - sformatowany (skrócony) ³añcuch \c _errorDesc
* \return kod b³edu \c LV_FAIL
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
	std::strcpy(*_formattedErrorDesc, errDesc.c_str());	// errDesc na pewno jest krótszy ni¿ MAX_ERROR_STRING
	return retCode::LV_FAIL;
}