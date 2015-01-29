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

#if GTEST_HAS_PARAM_TEST
using ::testing::TestWithParam;
using ::testing::Values;
/**
* \brief Parametric test fixture class
* \details Load and free relevant library before every test
* \warning W przypadku budowania pod VS na podstawie solucji wygenerowanej przez cmake, wszyskie pliki wynikowe s¹ umieszczane
* w podkatalogu \c Debug, a w przypadku czystego \b nmake nie s¹. To powoduje problemy z wzglêdnymi œcierzkami w teœcie
*/
class DLL_Tests : public TestWithParam<const char *> {
protected:
	BOOL init_error;
	HINSTANCE hinstLib;
	pLV_WeldDetectApprox_t pLV_WeldDetectApprox;  // pointer to function from DLL
	const char* testname;

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
		testname = GetParam();
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
#endif

/**
* \test DLL_Tests,_LV_WeldDetectApproxd
* \brief Finds weld line calling DLL
* \pre Set of images
* \post File \c DLL_*.out
* \author PB
* \date 2014/10/24
*/
TEST_P(DLL_Tests,_LV_WeldDetectApprox)
{
	ASSERT_FALSE(init_error); // expect no error during initialization

	// obs³uga b³êdów
	retCode ret;
	char err[MAX_ERROR_STRING];

	// input data
	unsigned int rows, cols;
	std::unique_ptr<double[]> rtgtmp_data;
	ASSERT_NO_THROW(C_MatlabExchange::ReadData(testname, rtgtmp_data, rows, cols));
	// konwersja INT
	UINT16* inTab = new UINT16[rows*cols];
	for (unsigned int a=0;a<rows*cols;a++)
		inTab[a] = static_cast<UINT16>(rtgtmp_data[a]);

	// output data
	UINT16* outTab = new UINT16[rows*cols];

	// wywo³anie
	ret = pLV_WeldDetectApprox(inTab, outTab, rows, cols, err);
	EXPECT_EQ(ret, retCode::LV_OK);

	// nagranie wyników
	// usuniecie kropki z testname zeby w matlabie nazwa by³a poprawna
	std::string matlab_name(testname);
	std::string::size_type extPos = matlab_name.find_last_of(".");
	if(extPos!=string::npos)
		matlab_name = matlab_name.substr(0,extPos);
	C_MatlabExchange dump( (string("DLL_")+string(testname)+string(".out")).c_str() );
	dump.AddEntry2D<UINT16>(outTab,rows, cols, matlab_name.c_str());

	delete[] inTab;
	delete[] outTab;
}

// run test for old dataset
INSTANTIATE_TEST_CASE_P(
	dataSet1,
	DLL_Tests,
	::testing::Values("testimag1.dat","testimag2.dat","testimag3.dat","testimag4.dat","testimag5.dat","testimag6.dat","testimag7.dat","testimag8.dat","testimag9.dat",
	"testimag10.dat","testimag11.dat","testimag12.dat","testimag13.dat","testimag14.dat","testimag15.dat","testimag16.dat","testimag17.dat","testimag18.dat",
	"testimag19.dat","testimag20.dat","testimag21.dat"));

// run test for new dataset
INSTANTIATE_TEST_CASE_P(
	dataSet2,
	DLL_Tests,
	::testing::Values("Sample-01-60kV-12mA-8s-IQI.tif.dat",
	"Sample-01-70kV-15mA-8s-IQI.tif.dat",
	"Sample-02-60kV-12mA-8s-IQI.tif.dat",
	"Sample-03-60kV-15mA-8s-IQI.tif.dat",
	"Sample-04-60kV-12mA-8s-IQI.tif.dat",
	"Sample-05-60kV-12mA-8s-IQI.tif.dat",
	"Sample-06-60kV-12mA-8s-IQI-A.tif.dat",
	"Sample-06-60kV-12mA-8s-IQI-B.tif.dat",
	"Sample-07-60kV-15mA-8s-IQI.tif.dat",
	"Sample-08-70kV-15mA-11s-IQI.tif.dat",
	"Sample-09-60kV-12mA-8s-IQI-A.tif.dat",
	"Sample-09-60kV-12mA-8s-IQI-B.tif.dat",
	"Sample-10-60kV-12mA-8s-IQI.tif.dat",
	"Sample-11-60kV-12mA-8s-IQI.tif.dat",
	"Sample-12-60kV-12mA-8s-IQI-A.tif.dat",
	"Sample-12-60kV-12mA-8s-IQI-B.tif.dat",
	"Sample-13-65kV-12mA-8s-IQI.tif.dat",
	"Sample-14-70kV-15mA-8s-IQI.tif.dat",
	"Sample-15-70kV-15mA-8s-IQI.tif.dat",
	"Sample-17-60kV-12mA-8s-IQI.tif.dat",
	"Sample-18-70kV-15mA-8s-IQI-A.tif.dat",
	"Sample-18-70kV-15mA-8s-IQI-B.tif.dat",
	"Sample-20-60kV-12mA-8s-IQI.tif.dat"));