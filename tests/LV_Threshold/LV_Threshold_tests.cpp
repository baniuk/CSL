/**
* \file    LV_Threshold_tests.cpp
* \brief	Tests of public and private functions in LV_Threshold
* \author  PB
* \date    2014/10/11
*/

#include <windows.h>
#include "gtest/gtest.h"
#include "definitions.h"
#include "MatlabExchange/C_MatlabExchange.hpp"
#include "LV_Threshold/LV_Threshold.h"

using namespace std;

/// \copydoc ::LV_Thresh
typedef void (*pLV_Thresh_t)(UINT16*, UINT16*, UINT16, unsigned int, double, char*);

int main(int argc, char* argv[])
{
	int ret = 0;
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
	BOOL init_error;
	HINSTANCE hinstLib;
	pLV_Thresh_t pLV_Thresh;  // pointer to function from DLL

	// Initializes test environment
	virtual void SetUp()
	{
		init_error = FALSE;	// no error
		// wersja VS
		hinstLib = LoadLibrary(TEXT("../../../src/LV_Threshold/Debug/LV_Threshold.dll"));
		if(hinstLib==NULL)
		{
			cerr << "Error in LoadLibrary. Trying other directory" << endl;
			// wersja nmake
			hinstLib = LoadLibrary(TEXT("../../src/LV_Threshold/LV_Threshold.dll"));
			if(hinstLib==NULL)
			{
				init_error = TRUE;
				cerr << "Cant find DLL" << endl;
				return;
			}
		}

		// funkcje
		pLV_Thresh = (pLV_Thresh_t)GetProcAddress(hinstLib, "LV_Thresh");
		if(pLV_Thresh==nullptr)
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
* \test
* \brief
* \post
* \author PB
* \date 2014/10/11
*/
TEST_F(DLL_Tests,_Threshold)
{
	ASSERT_FALSE(init_error); // expect no error during initialization
}

/**
* \test STATIC_Test,_Threshold_1
* \brief Tests main procedre from static lib
* \pre Image \c im8bit.dat
* \post File \c LV_Threshold_tests.out
* \author PB
* \date 2014/10/11
*/
TEST(STATIC_Test,_Threshold_1)
{
	std::unique_ptr<double[]> data;
	unsigned int rows,cols;
	char err[MAX_ERROR_STRING];

	ASSERT_NO_THROW(C_MatlabExchange::ReadData("im8bit.dat",data, rows, cols));
	// konwersja INT
	UINT16* inTab = new UINT16[rows*cols];
	UINT16* outTab = new UINT16[rows*cols];
	for (unsigned int a=0;a<rows*cols;a++)
		inTab[a] = static_cast<UINT16>(data[a]);

	Sauv(inTab, outTab, rows, cols, 23, 0.05);
	C_MatlabExchange out("LV_Threshold_tests.out");
	out.AddEntry2D<UINT16>(outTab, rows, cols, "Sauv");

	delete[] inTab;
	delete[] outTab;
}

/**
* \test STATIC_Test,_Threshold_2
* \brief Tests main procedre from static lib
* \pre Image \c imag2.dat
* \post File \c LV_Threshold_tests_2.out
* \author PB
* \date 2014/10/11
*/
TEST(STATIC_Test,_Threshold_2)
{
	std::unique_ptr<double[]> data;
	unsigned int rows,cols;
	char err[MAX_ERROR_STRING];

	ASSERT_NO_THROW(C_MatlabExchange::ReadData("imag2.dat",data, rows, cols));
	// konwersja INT
	UINT16* inTab = new UINT16[rows*cols];
	UINT16* outTab = new UINT16[rows*cols];
	for (unsigned int a=0;a<rows*cols;a++)
		inTab[a] = static_cast<UINT16>(data[a]);

	Sauv(inTab, outTab, rows, cols, 57, 0.005);
	C_MatlabExchange out("LV_Threshold_tests_2.out");
	out.AddEntry2D<UINT16>(outTab, rows, cols, "imag2");

	delete[] inTab;
	delete[] outTab;
}