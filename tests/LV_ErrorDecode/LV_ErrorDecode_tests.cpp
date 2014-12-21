/**
 * \file LV_ErrorDecode_tests.cpp
 * \brief Tests for static and dynamic library
 * \author PB
 * \date 2014/12/18
 */

#include "gtest/gtest.h"
#include "LV_ErrorDecode/LV_ErrorDecode.h"

/**
 * \test ErrorDecode_static::getDllName_1
 * \brief Test decoding from error code to DLL name
 * \pre error code exists
 * \post expects correct dll names
 * \author PB
 * \date 2014/12/18
*/
TEST(ErrorDecode_static, getDllName_1)
{
	uint32_t errCode;
	std::string ret;

	errCode = 0x01000001;
	ret = getDllName(errCode);
	ASSERT_STREQ(ret.c_str(), "LV_FastMedian.dll");
}

/**
* \test ErrorDecode_static::getDllName_2
* \brief Test decoding from error code to DLL name
* \pre error code above range
* \post empty string
* \author PB
* \date 2014/12/18
*/
TEST(ErrorDecode_static, getDllName_2)
{
	uint32_t errCode;
	std::string ret;

	errCode = 1;
	ret = getDllName(errCode);
	ASSERT_TRUE(ret.empty());
}

/**
 * \test ErrorDecode_static::getErrorDescription_1
 * \brief Test if DLL not found
 * \pre eror number that is not related with any DLL
 * \post "Unknown error code"
 * \author PB
 * \date 2014/12/18
*/
TEST(ErrorDecode_static, getErrorDescription_1)
{
	std::string errDesc;
	errDesc = getErrorDescription(1);
	ASSERT_STREQ("Unknown error code", errDesc.c_str());
}

/**
 * \test ErrorDecode_static::getErrorDescription_2
 * \brief DLL not found on path
 * \pre code for existing DLL but DLL not found
 * \post  "library LV_FastMedian could not be found"
 * \author PB
 * \date 2014/12/18
*/
TEST(ErrorDecode_static, getErrorDescription_2)
{
	std::string errDesc;
	errDesc = getErrorDescription(0x01000001);
	std::cerr << errDesc << std::endl;
	ASSERT_STREQ("library LV_FastMedian.dll could not be found", 
		errDesc.c_str());
}

/**
* \test ErrorDecode_static::getErrorDescription_3
* \brief DLL found on path but no error ID
* \pre code for existing DLL on path but fo wrong string
* \post  "library LV_FastMedian could not be found"
* \author PB
* \date 2014/12/18
*/
TEST(ErrorDecode_static, getErrorDescription_3)
{
	std::string errDesc;
	errDesc = getErrorDescription(0xFFFFFF05);
	std::cerr << errDesc << std::endl;
	ASSERT_STRCASEEQ("Error of code: FFFFFF05 could not be found in library LV_ErrorDecode_dummyDLL.dll", 
		errDesc.c_str());
}

/**
* \test ErrorDecode_static::getErrorDescription_4
* \brief DLL found on path and found error ID
* \pre code for existing DLL and existing error ID
* \post  "Hello"
* \author PB
* \date 2014/12/18
*/
TEST(ErrorDecode_static, getErrorDescription_4)
{
	std::string errDesc;
	errDesc = getErrorDescription(0xFFFFFF00);
	std::cerr << errDesc << std::endl;
	ASSERT_STREQ("Hello", errDesc.c_str());
}