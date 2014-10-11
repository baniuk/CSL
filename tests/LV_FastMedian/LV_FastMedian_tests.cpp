/**
* \file    LV_FastMedian_tests.cpp
* \brief	Tests of public and private functions in LV_FastMedian.dll
* \author  PB
* \date    2014/01/22
*/

#include <windows.h>
#include "gtest/gtest.h"
#include "definitions.h"
#include "MatlabExchange/C_MatlabExchange.hpp"

using namespace std;

/// \copydoc ::LV_MedFilt
typedef void (*pLV_MedFilt_t)(UINT16*, UINT16*, UINT16, UINT16, UINT16, char*);

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
	pLV_MedFilt_t pLV_MedFilt;  // pointer to function from DLL

	// Initializes test environment
	virtual void SetUp()
	{
		init_error = FALSE;	// no error
		// wersja VS
		hinstLib = LoadLibrary(TEXT("../../../src/LV_FastMedian/Debug/LV_FastMedian.dll"));
		if(hinstLib==NULL)
		{
			cerr << "Error in LoadLibrary. Trying other directory" << endl;
			// wersja nmake
			hinstLib = LoadLibrary(TEXT("../../src/LV_FastMedian/LV_FastMedian.dll"));
			if(hinstLib==NULL)
			{
				init_error = TRUE;
				cerr << "Cant find DLL" << endl;
				return;
			}
		}

		// funkcje
		pLV_MedFilt = (pLV_MedFilt_t)GetProcAddress(hinstLib, "LV_MedFilt");
		if(pLV_MedFilt==nullptr)
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
* \test DLL_Tests:_FastMedian
* \brief Testuje filtrowanie algorytmem szybkiej mediany
* \post Wynik nagrany na dysku, weryfikacja w Matlabie
* \author PB
* \date 2014/10/02
* \todo Finish this test
*/
TEST_F(DLL_Tests,_FastMedian)
{
	ASSERT_FALSE(init_error); // expect no error during initialization
	std::unique_ptr<double[]> data;
	unsigned int rows,cols;
	char err[MAX_ERROR_STRING];
	C_MatlabExchange::ReadData("imag2.dat",data, rows, cols);
	// konwersja INT
	UINT16* inTab = new UINT16[rows*cols];
	for (unsigned int a=0;a<rows*cols;a++)
		inTab[a] = static_cast<UINT16>(data[a]);

	// tablica wyjściowa
	UINT16 *outTab = new UINT16[rows*cols];
	pLV_MedFilt(inTab, outTab, rows, cols, 31, err);

	C_MatlabExchange out("FastMedian.out");
	out.AddEntry2D<UINT16>(outTab,rows,cols,"filtered_image");
	std::cout << "Check FastMedian.out for results" << std::endl;
	delete[] inTab;
	delete[] outTab;
}