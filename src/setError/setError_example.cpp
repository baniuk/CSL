/**
* \file setError_example.cpp
* \brief Przykład użycia klasy setError
* \author PB
* \date 2014/10/02
*/

/**
* \brief Przykładowa funkcja z biblioteki która zwraca błąd przy użyciu setError
* \param[in] a - jakiś parametr formalny
* \param[in] b - jakiś parametr formalny
* \param[out] errDesc - wskaźnik przekazywane z LV wskazujący na tablicę \c char do której nalezy skopiowac komunikat o błędzie
* \return kod błędu \c LV_FAIL
* \retval retCode
* \author PB
* \date 2014/10/02
*/
retCode funkcja(UINT a, UINT b, char* errDesc)
{
	if(a<0)	// hipotetyczny błąd
	{
		// wyrzucenie opisu błedu i wyjście z funkcji
		return setError::throwError("<nazwa_DLL>::Wartość a jest mniejsza od 0",&errDesc);
	}
}