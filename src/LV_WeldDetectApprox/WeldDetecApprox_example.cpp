/**
* \file WeldDetecApprox_example.cpp
* \brief Przykład użycia wykrywania spawu
* \author PB
* \date 2014/10/24
*/

/**
* \brief Przykładowe użycie metod do detekcji spawu
* \retval void
* \author PB
* \date 2014/10/24
*/
void foo()
{
	double A, E;
	C_Point cp_x_start(10,0);	// punkt startowy
	ParamEstimation(rtg->data, rtg->_cols, rtg->_rows, (unsigned int)cp_x_start.getX(), A ,E); // parametry poczatkowe dla punktu startowego
	C_LineWeldApprox::setDefaultParams(A,60,0,E, 65535,600,1,20000, 0,50,-1,-20000); // ustawienie parametrów poczatkowych
	obj->SetProcedureParameters(50,cp_x_start); // inicjalizacja srodowiska, wielkosc bufora 100
	ret = obj->Start(4,0);	// krok

	// wyniki
	_lineOK = obj->getLineOK();
	_weldPos = obj->getweldPos();
}