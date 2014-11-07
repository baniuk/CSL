﻿/**
* \file    LV_WeldDetectApprox_tests.cpp
* \brief	Tests of public and private functions in LV_WeldDetectApprox
* \author  PB
* \date    2014/10/20
*/

#include "gtest/gtest.h"
#include "definitions.h"
#include "MatlabExchange/C_MatlabExchange.hpp"
#include "LV_WeldDetectApprox/C_LinearWeld.h"
#include "LV_WeldDetectApprox/ParamEstimation.h"
#include "C_Matrix_Container.h"

/**
* \test STATIC_ParamEstimation, _ParamEstimation_1
* \brief Evaluates \c A and \c E params of gauss function
* \details Evaluates one column from test image and returns \c a and \c E
* \pre testimag16.dat
* \post \c A and \c E evaluated for column 10 - compared to those from matlab (col 11)
* \author PB
* \date 2014/10/24
*/
TEST(STATIC_ParamEstimation, _ParamEstimation_1)
{
	C_Matrix_Container rtgtmp;
	C_MatlabExchange dump("ParamEstimation_1.out");

	rtgtmp.ReadBinary("testimag16.dat");

	double A,E;

	ParamEstimation(rtgtmp.data, rtgtmp._cols, rtgtmp._rows, 10, A, E);
	dump.AddEntry2D<double>(rtgtmp.data,rtgtmp._rows, rtgtmp._cols, "paramEstimationImage");
	EXPECT_EQ(45263-31467,A);
	EXPECT_EQ(31467, E);
}
/**
* \test STATIC_WeldDetexApprox,_WeldDetexApprox_1
* \brief Tests main procedre from static lib. The use of method is in examples: WeldDetecApprox_example.cpp
* \details Use \c weld_edge=0.2
* \pre Image \c testimag7.dat
* \post File \c WeldDetectApprox_7.out
* \see verify.m for result verification
* \author PB
* \date 2014/10/20
*/
TEST(STATIC_WeldDetexApprox, _WeldDetexApprox_7)
{
	std::unique_ptr<double[]> rtgtmp_data;
	Matrix_Container rtg;
	C_LinearWeld *obj;
	bool ret;
	const std::vector<bool> *_lineOK;
	const std::vector<C_WeldPos> *_weldPos;
	C_Matrix_Container lineok;
	C_Matrix_Container weldpos;
	bool data;
	C_WeldPos wp;

	C_MatlabExchange dump("WeldDetectApprox_7.out");
	ASSERT_NO_THROW(C_MatlabExchange::ReadData("testimag7.dat",rtgtmp_data,rtg._rows, rtg._cols));
	// convert to internal struct
	rtg.data = rtgtmp_data.get();
	obj = new C_LinearWeld(&rtg);

	double A, E;
	C_Point cp_x_start(10,0);	// punkt startowy
	ParamEstimation<double>(rtg.data, rtg._cols, rtg._rows, (unsigned int)cp_x_start.getX(), A ,E); // punkt startowy
	C_LineWeldApprox::setDefaultParams(A,60,0,E,
		65535,600,1,70000,
		0,50,-1,-20000);
	obj->SetProcedureParameters(50,cp_x_start); // inicjalizacja srodowiska, wielkosc bufora 100
	ret = obj->Start(4,0,0.2);	// krok
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

	delete obj;
}

/**
* \test STATIC_WeldDetexApprox,_WeldDetexApprox_2
* \brief Tests main procedre from static lib. Uses WSK sample. Use the following method for example generation:
* \code {.unparsed}
* load originals.mat
* originals{2} = imcrop(originals{2},[2346.5 778.5 3840 1032]); // z f:\Dokumenty\Dysk Google\Praca\Granty\CASELOT
* ExportArrayToFile(originals{2},'testimag2.dat')
* \endcode
* \details Use \c weld_edge=0.4
* \pre Image \c testimag2.dat
* \post File \c WeldDetectApprox_2.out
* \see verify.m for result verification
* \note Uses parameters for WSK dataset
* \author PB
* \date 2014/10/21
*/
TEST(STATIC_WeldDetexApprox,_WeldDetexApprox_2)
{
	std::unique_ptr<double[]> rtgtmp_data;
	Matrix_Container rtg;
	C_LinearWeld *obj;
	bool ret;
	const std::vector<bool> *_lineOK;
	const std::vector<C_WeldPos> *_weldPos;
	C_Matrix_Container lineok;
	C_Matrix_Container weldpos;
	bool data;
	C_WeldPos wp;

	C_MatlabExchange dump("WeldDetectApprox_2.out");
	ASSERT_NO_THROW(C_MatlabExchange::ReadData("testimag2.dat",rtgtmp_data,rtg._rows, rtg._cols));
	// convert to internal struct
	rtg.data = rtgtmp_data.get();
	obj = new C_LinearWeld(&rtg);

	double A, E;
	C_Point cp_x_start(10,0);	// punkt startowy
	ParamEstimation<double>(rtg.data, rtg._cols, rtg._rows, (unsigned int)cp_x_start.getX(), A ,E); // punkt startowy
	C_LineWeldApprox::setDefaultParams(A,60,0,E,
		65535,300,1,70000,
		0,10,-1,-20000);
	obj->SetProcedureParameters(100,cp_x_start); // inicjalizacja srodowiska, wielkosc bufora 100
	ret = obj->Start(4,0,0.4);	// krok
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

	delete obj;
}

/**
* \test STATIC_WeldDetexApprox,_WeldDetexApprox_16
* \brief Tests main procedre from static lib. Uses WSK sample. Use the following method for example generation:
* \code {.unparsed}
* load originals.mat
* originals{2} = imcrop(originals{2},[2346.5 778.5 3840 1032]); // z f:\Dokumenty\Dysk Google\Praca\Granty\CASELOT
* ExportArrayToFile(originals{2},'testimag2.dat')
* \endcode
* \details Use \c weld_edge=0.8
* \pre Image \c testimag16.dat
* \post File \c WeldDetectApprox_16.out
* \see verify.m for result verification
* \note Uses parameters for WSK dataset
* \author PB
* \date 2014/10/24
*/
TEST(STATIC_WeldDetexApprox,_WeldDetexApprox_16)
{
	std::unique_ptr<double[]> rtgtmp_data;
	Matrix_Container rtg;
	C_LinearWeld *obj;
	bool ret;
	const std::vector<bool> *_lineOK;
	const std::vector<C_WeldPos> *_weldPos;
	C_Matrix_Container lineok;
	C_Matrix_Container weldpos;
	bool data;
	C_WeldPos wp;

	C_MatlabExchange dump("WeldDetectApprox_16.out");
	ASSERT_NO_THROW(C_MatlabExchange::ReadData("testimag16.dat",rtgtmp_data,rtg._rows, rtg._cols));
	// convert to internal struct
	rtg.data = rtgtmp_data.get();
	obj = new C_LinearWeld(&rtg);

	double A, E;
	C_Point cp_x_start(10,0);	// punkt startowy
	ParamEstimation<double>(rtg.data, rtg._cols, rtg._rows, (unsigned int)cp_x_start.getX(), A ,E); // punkt startowy
	C_LineWeldApprox::setDefaultParams(A,60,0,E,
		65535,340,1,70000,
		0,10,-1,-20000);
	obj->SetProcedureParameters(100,cp_x_start); // inicjalizacja srodowiska, wielkosc bufora 100
	ret = obj->Start(4,0,0.8);	// krok
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

	delete obj;
}