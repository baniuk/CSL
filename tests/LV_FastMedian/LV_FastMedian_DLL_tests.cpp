/**
* \file    LV_FastMedian_DLL_tests.cpp
* \brief	Tests of public and private functions in LV_FastMedian.dll
* \author  PB
* \date    2014/01/22
*/

#include <windows.h>
#include "gtest/gtest.h"
#include "definitions.h"
#include "MatlabExchange/C_MatlabExchange.hpp"
#include "LV_FastMedian/errordef.h"

using namespace std;

/// \copydoc ::LV_MedFilt
typedef retCode (*pLV_MedFilt_t)(UINT16*, UINT16*, UINT16, UINT16, UINT16);

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
* \test DLL_Tests:_FastMedian_evenmask
* \brief Testuje filtrowanie algorytmem szybkiej mediany dla maski 31
* \pre imag2.dat
* \post Błąd LV_FAIL oraz komunikat
* \author PB
* \date 2014/11/07
*/
TEST_F(DLL_Tests,_FastMedian_evenmask)
{
	ASSERT_FALSE(init_error); // expect no error during initialization
	retCode ret;
	std::unique_ptr<double[]> data;
	unsigned int rows,cols;
	rows = cols = 1024;
	// konwersja INT
	UINT16* inTab = new UINT16[rows*cols];
	// tablica wyjściowa
	UINT16 *outTab = new UINT16[rows*cols];
	ret = pLV_MedFilt(inTab, outTab, rows, cols, 30);
	EXPECT_EQ(ret, IDS_EVENMASK);

	delete[] inTab;
	delete[] outTab;
}

/**
* \test DLL_Tests:_FastMedian_imag2
* \brief Testuje filtrowanie algorytmem szybkiej mediany dla maski 31
* \pre imag2.dat
* \post imag2.out - wynik nagrany na dysku, weryfikacja w Matlabie
* \author PB
* \date 2014/10/02
*/
TEST_F(DLL_Tests,_FastMedian_imag2)
{
	ASSERT_FALSE(init_error); // expect no error during initialization
	retCode ret;
	std::unique_ptr<double[]> data;
	unsigned int rows,cols;
	ASSERT_NO_THROW(C_MatlabExchange::ReadData("imag2.dat",data, rows, cols));
	// konwersja INT
	UINT16* inTab = new UINT16[rows*cols];
	for (unsigned int a=0;a<rows*cols;a++)
		inTab[a] = static_cast<UINT16>(data[a]);

	// tablica wyjściowa
	UINT16 *outTab = new UINT16[rows*cols];
	ret = pLV_MedFilt(inTab, outTab, rows, cols, 31);
	EXPECT_EQ(ret, retCode::LV_OK);

	C_MatlabExchange out("imag2.out");
	out.AddEntry2D<UINT16>(outTab,rows,cols,"filtered_image");
	delete[] inTab;
	delete[] outTab;
}

/**
* \test DLL_Tests:_FastMedian_testimag1
* \brief Testuje filtrowanie algorytmem szybkiej mediany dla maski 31
* \pre testimag1.dat
* \post testimag1.out - wynik nagrany na dysku, weryfikacja w Matlabie
* \author PB
* \date 2014/11/07
*/
TEST_F(DLL_Tests,_FastMedian_testimag1)
{
	ASSERT_FALSE(init_error); // expect no error during initialization
	retCode ret;
	std::unique_ptr<double[]> data;
	unsigned int rows,cols;
	ASSERT_NO_THROW(C_MatlabExchange::ReadData("testimag1.dat",data, rows, cols));
	// konwersja INT
	UINT16* inTab = new UINT16[rows*cols];
	for (unsigned int a=0;a<rows*cols;a++)
		inTab[a] = static_cast<UINT16>(data[a]);

	// tablica wyjściowa
	UINT16 *outTab = new UINT16[rows*cols];
	ret = pLV_MedFilt(inTab, outTab, rows, cols, 31);
	EXPECT_EQ(ret, retCode::LV_OK);
	
	C_MatlabExchange out("testimag1.out");
	out.AddEntry2D<UINT16>(outTab,rows,cols,"filtered_image");
	delete[] inTab;
	delete[] outTab;
}

/**
* \test DLL_Tests:_FastMedian_testimag6
* \brief Testuje filtrowanie algorytmem szybkiej mediany dla maski 31
* \pre testimag6.dat
* \post testimag6.out - wynik nagrany na dysku, weryfikacja w Matlabie
* \author PB
* \date 2014/11/07
*/
TEST_F(DLL_Tests,_FastMedian_testimag6)
{
	ASSERT_FALSE(init_error); // expect no error during initialization
	retCode ret;
	std::unique_ptr<double[]> data;
	unsigned int rows,cols;
	ASSERT_NO_THROW(C_MatlabExchange::ReadData("testimag6.dat",data, rows, cols));
	// konwersja INT
	UINT16* inTab = new UINT16[rows*cols];
	for (unsigned int a=0;a<rows*cols;a++)
		inTab[a] = static_cast<UINT16>(data[a]);

	// tablica wyjściowa
	UINT16 *outTab = new UINT16[rows*cols];
	ret = pLV_MedFilt(inTab, outTab, rows, cols, 31);
	EXPECT_EQ(ret, retCode::LV_OK);
	
	C_MatlabExchange out("testimag6.out");
	out.AddEntry2D<UINT16>(outTab,rows,cols,"filtered_image");
	delete[] inTab;
	delete[] outTab;
}

/**
* \test DLL_Tests:_FastMedian_testimag9
* \brief Testuje filtrowanie algorytmem szybkiej mediany dla maski 31
* \pre testimag9.dat
* \post testimag9.out - wynik nagrany na dysku, weryfikacja w Matlabie
* \author PB
* \date 2014/11/07
*/
TEST_F(DLL_Tests,_FastMedian_testimag9)
{
	ASSERT_FALSE(init_error); // expect no error during initialization
	retCode ret;
	std::unique_ptr<double[]> data;
	unsigned int rows,cols;
	ASSERT_NO_THROW(C_MatlabExchange::ReadData("testimag9.dat",data, rows, cols));
	// konwersja INT
	UINT16* inTab = new UINT16[rows*cols];
	for (unsigned int a=0;a<rows*cols;a++)
		inTab[a] = static_cast<UINT16>(data[a]);

	// tablica wyjściowa
	UINT16 *outTab = new UINT16[rows*cols];
	ret = pLV_MedFilt(inTab, outTab, rows, cols, 31);
	EXPECT_EQ(ret, retCode::LV_OK);
	
	C_MatlabExchange out("testimag9.out");
	out.AddEntry2D<UINT16>(outTab,rows,cols,"filtered_image");
	delete[] inTab;
	delete[] outTab;
}

/**
* \test DLL_Tests:_FastMedian_testimag17_m31
* \brief Testuje filtrowanie algorytmem szybkiej mediany dla maski 31
* \pre testimag17.dat
* \post testimag17m31.out - wynik nagrany na dysku, weryfikacja w Matlabie
* \author PB
* \date 2014/11/07
*/
TEST_F(DLL_Tests,_FastMedian_testimag17_m31)
{
	ASSERT_FALSE(init_error); // expect no error during initialization
	retCode ret;
	std::unique_ptr<double[]> data;
	unsigned int rows,cols;
	ASSERT_NO_THROW(C_MatlabExchange::ReadData("testimag17.dat",data, rows, cols));
	// konwersja INT
	UINT16* inTab = new UINT16[rows*cols];
	for (unsigned int a=0;a<rows*cols;a++)
		inTab[a] = static_cast<UINT16>(data[a]);

	// tablica wyjściowa
	UINT16 *outTab = new UINT16[rows*cols];
	ret = pLV_MedFilt(inTab, outTab, rows, cols, 31);
	EXPECT_EQ(ret, retCode::LV_OK);
	
	C_MatlabExchange out("testimag17m31.out");
	out.AddEntry2D<UINT16>(outTab,rows,cols,"filtered_image");
	delete[] inTab;
	delete[] outTab;
}

/**
* \test DLL_Tests:_FastMedian_testimag17_m51
* \brief Testuje filtrowanie algorytmem szybkiej mediany dla maski 51
* \pre testimag17.dat
* \post testimag17m31.out - wynik nagrany na dysku, weryfikacja w Matlabie
* \author PB
* \date 2014/11/07
*/
TEST_F(DLL_Tests,_FastMedian_testimag17_m51)
{
	ASSERT_FALSE(init_error); // expect no error during initialization
	retCode ret;
	std::unique_ptr<double[]> data;
	unsigned int rows,cols;
	ASSERT_NO_THROW(C_MatlabExchange::ReadData("testimag17.dat",data, rows, cols));
	// konwersja INT
	UINT16* inTab = new UINT16[rows*cols];
	for (unsigned int a=0;a<rows*cols;a++)
		inTab[a] = static_cast<UINT16>(data[a]);

	// tablica wyjściowa
	UINT16 *outTab = new UINT16[rows*cols];
	ret = pLV_MedFilt(inTab, outTab, rows, cols, 51);
	EXPECT_EQ(ret, retCode::LV_OK);
	
	C_MatlabExchange out("testimag17m51.out");
	out.AddEntry2D<UINT16>(outTab,rows,cols,"filtered_image");
	delete[] inTab;
	delete[] outTab;
}

/**
* \test DLL_Tests:_FastMedian_testimag17_m91
* \brief Testuje filtrowanie algorytmem szybkiej mediany dla maski 91
* \pre testimag17.dat
* \post testimag17m31.out - wynik nagrany na dysku, weryfikacja w Matlabie
* \author PB
* \date 2014/11/07
*/
TEST_F(DLL_Tests,_FastMedian_testimag17_m91)
{
	ASSERT_FALSE(init_error); // expect no error during initialization
	retCode ret;
	std::unique_ptr<double[]> data;
	unsigned int rows,cols;
	ASSERT_NO_THROW(C_MatlabExchange::ReadData("testimag17.dat",data, rows, cols));
	// konwersja INT
	UINT16* inTab = new UINT16[rows*cols];
	for (unsigned int a=0;a<rows*cols;a++)
		inTab[a] = static_cast<UINT16>(data[a]);

	// tablica wyjściowa
	UINT16 *outTab = new UINT16[rows*cols];
	ret = pLV_MedFilt(inTab, outTab, rows, cols, 91);
	EXPECT_EQ(ret, retCode::LV_OK);
	
	C_MatlabExchange out("testimag17m91.out");
	out.AddEntry2D<UINT16>(outTab,rows,cols,"filtered_image");
	delete[] inTab;
	delete[] outTab;
}

/**
* \test DLL_Tests:_FastMedian_testimag17_m3
* \brief Testuje filtrowanie algorytmem szybkiej mediany dla maski 3
* \pre testimag17.dat
* \post testimag17m31.out - wynik nagrany na dysku, weryfikacja w Matlabie
* \author PB
* \date 2014/11/07
*/
TEST_F(DLL_Tests,_FastMedian_testimag17_m3)
{
	ASSERT_FALSE(init_error); // expect no error during initialization
	retCode ret;
	std::unique_ptr<double[]> data;
	unsigned int rows,cols;
	ASSERT_NO_THROW(C_MatlabExchange::ReadData("testimag17.dat",data, rows, cols));
	// konwersja INT
	UINT16* inTab = new UINT16[rows*cols];
	for (unsigned int a=0;a<rows*cols;a++)
		inTab[a] = static_cast<UINT16>(data[a]);

	// tablica wyjściowa
	UINT16 *outTab = new UINT16[rows*cols];
	ret = pLV_MedFilt(inTab, outTab, rows, cols, 3);
	EXPECT_EQ(ret, retCode::LV_OK);
	
	C_MatlabExchange out("testimag17m3.out");
	out.AddEntry2D<UINT16>(outTab,rows,cols,"filtered_image");
	delete[] inTab;
	delete[] outTab;
}

