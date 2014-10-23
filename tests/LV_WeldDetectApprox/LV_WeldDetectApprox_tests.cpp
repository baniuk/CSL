/**
* \file    LV_WeldDetectApprox_tests.cpp
* \brief	Tests of public and private functions in LV_WeldDetectApprox
* \author  PB
* \date    2014/10/20
*/

#include <windows.h>
#include "gtest/gtest.h"
#include "definitions.h"
#include "MatlabExchange/C_MatlabExchange.hpp"
#include "LV_WeldDetectApprox/C_LinearWeld.h"

using namespace std;

int main(int argc, char* argv[])
{
	int ret = 0;
	//	HANDLE hLogFile;
	//	time_t seconds;
	//	time ( &seconds );
	//	hLogFile = CreateFile("C_WeldLineDetect.mylog", FILE_APPEND_DATA,
	//		FILE_SHARE_WRITE, NULL, CREATE_ALWAYS,
	//		FILE_ATTRIBUTE_NORMAL, NULL);
	//	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG|_CRTDBG_MODE_FILE);
	//	_CrtSetReportFile(_CRT_WARN, hLogFile);
	//	_RPT1(_CRT_WARN,  "The current local time is: %s\n", ctime(&seconds) );

	::testing::InitGoogleTest(&argc, argv);
	ret = RUN_ALL_TESTS();
	return ret;
}

/**
* \brief Test fixture class
* \details Load and free relevant library before every test
* \warning W przypadku budowania pod VS na podstawie solucji wygenerowanej przez cmake, wszyskie pliki wynikowe są umieszczane
* w podkatalogu \c Debug, a w przypadku czystego \b nmake nie są. To powoduje problemy z względnymi ścierzkami w teście
*/
class DLL_Tests : public ::testing::Test {
protected:

	// Initializes test environment
	virtual void SetUp()
	{
	}

	virtual void TearDown()
	{
	}

	// Objects declared here can be used by all tests in the test case for Foo.
};

/**
* \test STATIC_WeldDetexApprox,_WeldDetexApprox_1
* \brief Tests main procedre from static lib
* \pre Image \c testimag1.dat
* \post File \c WeldDetectApprox_1.out
* \see verify.m for result verification
* \author PB
* \date 2014/10/20
*/
TEST(STATIC_WeldDetexApprox,DISABLED__WeldDetexApprox_1)
{
	C_Matrix_Container *rtg;
	C_LinearWeld *obj;
	bool ret;
	const std::vector<bool> *_lineOK;
	const std::vector<C_WeldPos> *_weldPos;
	C_Matrix_Container lineok;
	C_Matrix_Container weldpos;
	bool data;
	C_WeldPos wp;

	C_MatlabExchange dump("WeldDetectApprox_1.out");
	rtg = new C_Matrix_Container();
	rtg->ReadBinary("testimag1.dat");
	obj = new C_LinearWeld(rtg);

	C_LineWeldApprox::setDefaultParams(1060,160,0,0,
		65535,600,1,20000,
		0,50,-1,-20000);
	C_Point cp_x_start(10,0);	// punkt startowy
	obj->SetProcedureParameters(50,cp_x_start); // inicjalizacja srodowiska, wielkosc bufora 100
	ret = obj->Start(1,0);	// krok
	ASSERT_TRUE(ret);

	_lineOK = obj->getLineOK();
	_weldPos = obj->getweldPos();

	lineok.AllocateData(1,(unsigned int)_lineOK->size());
	weldpos.AllocateData(6,(unsigned int)_weldPos->size());

	for(unsigned int l=0;l<_lineOK->size();++l)
	{
		data = _lineOK->at(l);
		lineok.SetPixel(0,l,(double)data);

		wp = _weldPos->at(l);
		weldpos.SetPixel(0,l, wp.D.getX());
		weldpos.SetPixel(1,l, wp.D.getY());
		weldpos.SetPixel(2,l, wp.S.getX());
		weldpos.SetPixel(3,l, wp.S.getY());
		weldpos.SetPixel(4,l, wp.G.getX());
		weldpos.SetPixel(5,l, wp.G.getY());
	}

	dump.AddEntry2D<double>(lineok.data, lineok._rows, lineok._cols, "lineok");
	dump.AddEntry2D<double>(weldpos.data, weldpos._rows, weldpos._cols, "weldpos");

	delete rtg;
	delete obj;
}

/**
* \test STATIC_WeldDetexApprox,_WeldDetexApprox_2
* \brief Tests main procedre from static lib. Uses WSK sample. Use the following method for example generation:
* \code {.unparsed}
* load originals.mat
* originals{2} = imcrop(originals{2},[2346.5 778.5 3840 1032]); // z f:\Dokumenty\Dysk Google\Praca\Granty\CASELOT
* savebinarymatrix(originals{2},'testimag2.dat')
* \endcode
* \pre Image \c testimag2.dat
* \post File \c WeldDetectApprox_2.out
* \see verify.m for result verification
* \note Uses parameters for WSK dataset
* \author PB
* \date 2014/10/21
*/
TEST(STATIC_WeldDetexApprox,_WeldDetexApprox_2)
{
	C_Matrix_Container *rtg;
	C_LinearWeld *obj;
	bool ret;
	const std::vector<bool> *_lineOK;
	const std::vector<C_WeldPos> *_weldPos;
	C_Matrix_Container lineok;
	C_Matrix_Container weldpos;
	bool data;
	C_WeldPos wp;

	C_MatlabExchange dump("WeldDetectApprox_2.out");
	rtg = new C_Matrix_Container();
	rtg->ReadBinary("testimag2.dat");
	obj = new C_LinearWeld(rtg);

	C_LineWeldApprox::setDefaultParams(45000,60,0,0,
		65535,120,1,70000,
		0,30,-1,-20000);
	C_Point cp_x_start(10,0);	// punkt startowy
	obj->SetProcedureParameters(100,cp_x_start); // inicjalizacja srodowiska, wielkosc bufora 100
	ret = obj->Start(1,0);	// krok
	ASSERT_TRUE(ret);

	_lineOK = obj->getLineOK();
	_weldPos = obj->getweldPos();

	lineok.AllocateData(1,(unsigned int)_lineOK->size());
	weldpos.AllocateData(6,(unsigned int)_weldPos->size());

	for(unsigned int l=0;l<_lineOK->size();++l)
	{
		data = _lineOK->at(l);
		lineok.SetPixel(0,l,(double)data);

		wp = _weldPos->at(l);
		weldpos.SetPixel(0,l, wp.D.getX());
		weldpos.SetPixel(1,l, wp.D.getY());
		weldpos.SetPixel(2,l, wp.S.getX());
		weldpos.SetPixel(3,l, wp.S.getY());
		weldpos.SetPixel(4,l, wp.G.getX());
		weldpos.SetPixel(5,l, wp.G.getY());
	}

	dump.AddEntry2D<double>(lineok.data, lineok._rows, lineok._cols, "lineok");
	dump.AddEntry2D<double>(weldpos.data, weldpos._rows, weldpos._cols, "weldpos");

	delete rtg;
	delete obj;
}