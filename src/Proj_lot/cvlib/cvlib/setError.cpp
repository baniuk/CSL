#include <string>
#include "StdAfx.h"
#include "setError/setError.h"
#include "definitions.h"


retCode setError::throwError(const char* _errorDesc, char** _formattedErrorDesc)
{
	std::string errDesc(_errorDesc);	// c++ string copy of const char* string
	if (errDesc.length() > MAX_ERROR_STRING-1)	// jeœli za d³ugi to tniemy (+ miejsce na \0)
		errDesc.resize(MAX_ERROR_STRING-1);
	// kopiowanie skróconego ³añcucha do pamiêci LV
	std::strcpy(*_formattedErrorDesc, errDesc.c_str());	// errDesc na pewno jest krótszy niż MAX_ERROR_STRING
	return retCode::LV_FAIL;
}
