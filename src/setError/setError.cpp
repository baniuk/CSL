/**
* \file setError.cpp
* \brief Implementacja klasy setError
* \author PB
* \date 2014/10/02
*/

#include "setError/setError.h"

/**
* \brief Zwraca sformatowany �a�cuch b�edu o okreslonej d�ugo�ci
* \details Automatycznie kontroluje d�ugo�� �a�cucha opisuj�cego b��d aby nie dopu�ci� do przekroczenia pami�ci
* przydzielonej w LV na ten �a�cuch. Za d�ugi komunikat jet przycinany bez zwracania jakiejkolwiek informacji o
* przekroczeniu dozwolonej d�ugo�ci \c MAX_ERROR_STRING
* \param[in] _errorDesc - la�cuch z opisem b��du
* \param[out] _formattedErrorDesc - sformatowany (skr�cony) �a�cuch \c _errorDesc
* \return kod b�edu \c LV_FAIL
* \retval retCode
* \author PB
* \date 2014/10/02
* \see definitions.h
*/
retCode setError::throwError(const char* _errorDesc, char** _formattedErrorDesc)
{
	std::string errDesc(_errorDesc);	// c++ string copy of const char* string
	if (errDesc.length() > MAX_ERROR_STRING-1)	// je�li za d�ugi to tniemy (+ miejsce na \0)
		errDesc.resize(MAX_ERROR_STRING-1);
	// kopiowanie skr�conego �a�cucha do pami�ci LV
	std::strcpy(*_formattedErrorDesc, errDesc.c_str());	// errDesc na pewno jest kr�tszy ni� MAX_ERROR_STRING
	return retCode::LV_FAIL;
}