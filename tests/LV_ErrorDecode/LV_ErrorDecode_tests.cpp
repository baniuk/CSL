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

	errCode = 10001;
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