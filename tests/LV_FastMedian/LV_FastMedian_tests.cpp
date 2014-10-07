/**
* \file    TEST_LV_FastMEdian.cpp
* \brief	Tests of public and private functions in LV_FastMedian.dll
* \author  PB
* \date    2014/01/22
*/

#include <windows.h>
#include "gtest/gtest.h"
#include "definitions.h"

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
	unsigned short *input_image;	// input image
	unsigned short *output_image;
	// Przygotowanie danych dla funkcji
	// Tymczasowe readbinary i konwersja do formatu dla
	/*
	C_MATRIX_LOAD(tmp_input_image,"../../../../tests/LV_FastMedian/data/testimag1.dat"); // load test file
	tmp_input_image.Normalize(0,1);	// normalization
	input_image = new unsigned short[tmp_input_image.GetNumofElements()];
	if(input_image==NULL)
	{
	cerr << "Error in memory allocation" << endl;
	init_error = TRUE;
	}
	for(unsigned int a=0;a<tmp_input_image.GetNumofElements();a++)
	input_image[a] = static_cast<unsigned short>(floor(65535*tmp_input_image.data[a]+0.5));
	output_image = new unsigned short[tmp_input_image.GetNumofElements()];
	if(output_image==NULL)
	{
	cerr << "Error in memory allocation" << endl;
	init_error = TRUE;
	}

	// wywołanie funkcji
	LV_MedFilt31(input_image,output_image,tmp_input_image._rows,tmp_input_image._cols);
	// nagranie wyjścia
	C_DumpAll dump("../../../../tests/LV_FastMedian/data/test_out.dat");
	C_Matrix_Container out;
	out.AllocateData(tmp_input_image._rows,tmp_input_image._cols);
	for(unsigned int a=0;a<tmp_input_image.GetNumofElements();a++)
	out.data[a] = static_cast<double>(output_image[a]);
	dump.AddEntry(&out,"outimage");
	dump.AddEntry(&tmp_input_image,"inimage");

	SAFE_DELETE(input_image);
	SAFE_DELETE(output_image);

	cout << "Results in /data/test_out.dat" << endl;
	*/
}