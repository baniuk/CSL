/**
* \file    LV_WeldDetectApprox_DLL_tests.cpp
* \brief	Tests of public function exported from DLL LV_WeldDetectApprox
* \author  PB
* \date    2014/10/24
*/

#include "gtest/gtest.h"
#include "definitions.h"
#include "MatlabExchange/C_MatlabExchange.hpp"
#include "LV_WeldDetectApprox/C_LinearWeld.h"
#include "LV_WeldDetectApprox/ParamEstimation.h"
#include "C_Matrix_Container.h"

using namespace std;

/// \copydoc ::LV_WeldDetectApprox
typedef retCode (*pLV_WeldDetectApprox_t)(UINT16*, UINT16*, UINT16, UINT16, char*);

/**
* \brief Test fixture class
* \details Load and free relevant library before every test
* \warning W przypadku budowania pod VS na podstawie solucji wygenerowanej przez cmake, wszyskie pliki wynikowe s¹ umieszczane
* w podkatalogu \c Debug, a w przypadku czystego \b nmake nie s¹. To powoduje problemy z wzglêdnymi œcierzkami w teœcie
*/
class DLL_Tests : public ::testing::Test {
protected:
	BOOL init_error;
	HINSTANCE hinstLib;
	pLV_WeldDetectApprox_t pLV_WeldDetectApprox;  // pointer to function from DLL

	// Initializes test environment
	virtual void SetUp()
	{
		init_error = FALSE;	// no error
		// wersja VS
		hinstLib = LoadLibrary(TEXT("../../../src/LV_WeldDetectApprox/Debug/LV_WeldDetectApprox.dll"));
		if(hinstLib==NULL)
		{
			// wersja nmake
			hinstLib = LoadLibrary(TEXT("../../src/LV_WeldDetectApprox/LV_WeldDetectApprox.dll"));
			if(hinstLib==NULL)
			{
				init_error = TRUE;
				cerr << "Cant find DLL" << endl;
				return;
			}
		}

		// funkcje
		pLV_WeldDetectApprox = (pLV_WeldDetectApprox_t)GetProcAddress(hinstLib, "LV_WeldDetectApprox");
		if(pLV_WeldDetectApprox==nullptr)
		{
			cerr << "Error in GetProcAddress" << endl;
			init_error = TRUE;
			return;
		}
	}

	virtual void TearDown()
	{
		FreeLibrary(hinstLib);
	}

	// Objects declared here can be used by all tests in the test case for Foo.
};

/**
* \test DLL_Tests,_LV_WeldDetectApproxd
* \brief Finds weld line calling DLL
* \pre testimag16.dat image
* \post File \c WeldDetectApprox_16_DLL.out
* \author PB
* \date 2014/10/24
* \todo Finish after implementing OpenCV regions
*/
TEST_F(DLL_Tests,_LV_WeldDetectApprox)
{
	ASSERT_FALSE(init_error); // expect no error during initialization
}