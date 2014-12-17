#include <windows.h>
#include <iostream>
#include "gtest/gtest.h"
// TODO Dodac dokumentacje wszêdzie
int main(int argc, char* argv[])
{
	int ret = 0;
	::testing::InitGoogleTest(&argc, argv);
	ret = RUN_ALL_TESTS();
	return ret;
}

/**
 * \test ErrorHandling::lodLib
 * \brief 
 * \details
 * \pre {warunki pocz¹tkowe}
 * \post {wynik testu}
 * \author PB
 * \date 2014/12/17
 * \note
 * \warning
 * \see
*/
TEST(ErrorHandling, loadLib)
{
	BOOL init_error;
	HINSTANCE hinstLib;
	hinstLib = LoadLibrary(
		TEXT("../../../tests/ErrorHandling/Debug/ErrorDecoder.dll"));
	if (hinstLib == NULL)
	{
		// wersja nmake
		hinstLib = LoadLibrary(
			TEXT("../../tests/ErrorHandling/ErrorDecoder.dll"));
		if (hinstLib == NULL)
		{
			init_error = TRUE;
			std::cerr << "Cant find DLL" << std::endl;
			FAIL();
		}
	}
	FreeLibrary(hinstLib);
}

TEST(ReadResource, readString)
{
	BOOL init_error;
	HINSTANCE hinstLib;
	hinstLib = LoadLibrary(
		TEXT("../../../tests/ErrorHandling/Debug/ErrorHandling_DLL.dll"));
	if (hinstLib == NULL)
	{
		// wersja nmake
		hinstLib = LoadLibrary(
			TEXT("../../tests/ErrorHandling/ErrorHandling_DLL.dll"));
		if (hinstLib == NULL)
		{
			init_error = TRUE;
			std::cerr << "Cant find DLL" << std::endl;
			FAIL();
		}
	}
	// TODO Load STRINGTABLE here

	char buffer[512];
	int retVal;
	retVal = LoadString(hinstLib,
		102,
		buffer,
		512);
	FreeLibrary(hinstLib);
	std::cout << "Read string:" << buffer << "retval: " << retVal << std::endl;
	ASSERT_NE(retVal, 0);
}