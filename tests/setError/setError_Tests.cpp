/**
* \file setError_Tests.cpp
* \brief Testy biblioteki setError
* \author PB
* \date 2014/10/02
*/

#include "setError/setError.h"
#include "gtest/gtest.h"

int main(int argc, char* argv[])
{
	int ret = 0;
	::testing::InitGoogleTest(&argc, argv);
	ret = RUN_ALL_TESTS();
	return ret;
}

/**
* \test setError:_returnValue
* \brief Zwraca kod b³êdu
* \post Expect LV_FAIL
* \author PB
* \date 2014/10/02
*/
TEST(setError,_returnValue)
{
	char tab[MAX_ERROR_STRING];
	char* ptr = static_cast<char*>(tab);
	EXPECT_EQ(retCode::LV_FAIL, setError::throwError("Opis bledu",&ptr));
}

/**
* \test setError:_returnString
* \brief Zwraca kod b³êdu
* \post Expect LV_FAIL and original string
* \author PB
* \date 2014/10/02
*/
TEST(setError,_returnString)
{
	// symulacja srodowiska LV
	char LV_TAB[MAX_ERROR_STRING];
	char* ptr = LV_TAB;
	// opis bledu
	const char* blad = "Opis bledu";
	// wywo³anie metody
	retCode ret = setError::throwError(blad, &ptr);
	EXPECT_EQ(retCode::LV_FAIL, ret);
	EXPECT_STRCASEEQ(blad, LV_TAB);
	//	std::cout << LV_TAB << std::endl;
}

/**
* \test setError:_returnLongString
* \brief Zwraca za d³ugi ³añcuch (przycinanie)
* \post Expect LV_FAIL and cut string
* \author PB
* \date 2014/10/02
*/
TEST(setError,_returnLongString)
{
	// symulacja srodowiska LV
	char LV_TAB[MAX_ERROR_STRING];
	char* ptr = LV_TAB;
	// opis bledu
	ASSERT_EQ(MAX_ERROR_STRING,256); // test przystosowany do 256 znaków
	const char* blad = "1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
		"1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
		"12345678901234567890123456789012345678901234567890ABCDEF";// 256 znaków + /0
	const char* expected =  "1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
		"1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
		"12345678901234567890123456789012345678901234567890ABCDE";// 255 znaków + /0
	// wywo³anie metody
	retCode ret = setError::throwError(blad, &ptr);
	EXPECT_EQ(retCode::LV_FAIL, ret);
	EXPECT_STRCASEEQ(expected, LV_TAB);
	//	std::cout << LV_TAB << std::endl;
}