/**
 * \file LV_FastMedian_static_tests.cpp
 * \brief Static test for FastMedian
 * \author PB
 * \date 2015/01/24
 */

#include "gtest/gtest.h"
#include "definitions.h"
#include "LV_FastMedian/LV_fastMedian.h"
#include <memory>

/**
 * \test STATIC_FastMedian, _getPoint_lg
 * \brief Tests image wrapping in getPoint
 * \details getPoint can accept coordinates below 0 and above image size.
 * In this case should return mirrored points from inside of the image
 * Test left upper corner
 * \pre 100 x 100 image filled from 1 to 10000
 * \post mirrored points
 * \author PB
 * \date 2015/01/24
*/
TEST(STATIC_FastMedian, _getPoint_lg)
{
	OBRAZ obraz;
	obraz.cols = 100;
	obraz.rows = 100;
	obraz.tabsize = obraz.rows * obraz.cols;
	std::unique_ptr<UINT16[]>_obraz(new UINT16[obraz.tabsize]);
	obraz.tab = _obraz.get();

	// wype³nianie od o do 10000
	for (size_t i = 0; i < obraz.tabsize; i++)
		_obraz[i] = i;
	// test wype³nienia lewy górny róg
	{
		UINT16 res;
		res = getPoint(&obraz, 0, 0);
		EXPECT_EQ(res, 0);
	}
	// test wype³nienia prawy dolny róg
	{
		UINT16 res;
		res = getPoint(&obraz, 99, 99);
		EXPECT_EQ(res, 10000-1);
	}
	// test wype³nienia koniec pierwszego wiersza
	{
		UINT16 res;
		res = getPoint(&obraz, 0, 99);
		EXPECT_EQ(res, 99);
	}
	// maska 5 x 5
	// |-2,-2|-2,-1||-2, 0|-2, 1|-2, 2|
	// |-1,-2|-1,-1||-1, 0|-1, 1|-1, 2|
	// --------------------------------
	// | 0,-2| 0,-1|| 0, 0| 0, 1| 0, 2|
	// | 1,-2| 1,-1|| 1, 0| 1 ,1| 1 ,2|
	// | 2,-2| 2,-1|| 2, 0| 2, 1| 2, 2|
	//  
	// od lewego górnego rogu
	// 
	// |202|201||200 201 202|
	// |102|101||100 101 102|
	// ----------------------
	// |  2|  1||  0   1   2|
	// |102|101||100 101 102|
	// |202|201||200 201 202|
	// ------------
	// 300 301 302 303 ... 399
	// 400 401 402 403 ... 499
	// Bez odbijania
	{
		UINT16 res;
		// IV cwiartka
		res = getPoint(&obraz, 0, 0); EXPECT_EQ(res, 0);
		res = getPoint(&obraz, 0, 1); EXPECT_EQ(res, 1);
		res = getPoint(&obraz, 0, 2); EXPECT_EQ(res, 2);

		res = getPoint(&obraz, 1, 0); EXPECT_EQ(res, 100);
		res = getPoint(&obraz, 1, 1); EXPECT_EQ(res, 101);
		res = getPoint(&obraz, 1, 2); EXPECT_EQ(res, 102);

		res = getPoint(&obraz, 2, 0); EXPECT_EQ(res, 200);
		res = getPoint(&obraz, 2, 1); EXPECT_EQ(res, 201);
		res = getPoint(&obraz, 2, 2); EXPECT_EQ(res, 202);
		// I cwiartka
		res = getPoint(&obraz, -1, 0); EXPECT_EQ(res, 100);
		res = getPoint(&obraz, -1, 1); EXPECT_EQ(res, 101);
		res = getPoint(&obraz, -1, 2); EXPECT_EQ(res, 102);

		res = getPoint(&obraz, -2, 0); EXPECT_EQ(res, 200);
		res = getPoint(&obraz, -2, 1); EXPECT_EQ(res, 201);
		res = getPoint(&obraz, -2, 2); EXPECT_EQ(res, 202);
		// II cwiartka
		res = getPoint(&obraz, -1, -1); EXPECT_EQ(res, 101);
		res = getPoint(&obraz, -1, -2); EXPECT_EQ(res, 102);

		res = getPoint(&obraz, -2, -1); EXPECT_EQ(res, 201);
		res = getPoint(&obraz, -2, -2); EXPECT_EQ(res, 202);
		// III cwiartka
		res = getPoint(&obraz, 0, -1); EXPECT_EQ(res, 1);
		res = getPoint(&obraz, 0, -2); EXPECT_EQ(res, 2);

		res = getPoint(&obraz, 1, -1); EXPECT_EQ(res, 101);
		res = getPoint(&obraz, 1, -2); EXPECT_EQ(res, 102);

		res = getPoint(&obraz, 2, -1); EXPECT_EQ(res, 201);
		res = getPoint(&obraz, 2, -2); EXPECT_EQ(res, 202);
	}
}

/**
* \test STATIC_FastMedian, _getPoint_pd
* \brief Tests image wrapping in getPoint
* \details getPoint can accept coordinates below 0 and above image size.
* In this case should return mirrored points from inside of the image
* Test righ lower corner
* \pre 100 x 100 image filled from 1 to 10000
* \post mirrored points
* \author PB
* \date 2015/01/24
*/
TEST(STATIC_FastMedian, _getPoint_pd)
{
	OBRAZ obraz;
	obraz.cols = 100;
	obraz.rows = 100;
	obraz.tabsize = obraz.rows * obraz.cols;
	std::unique_ptr<UINT16[]>_obraz(new UINT16[obraz.tabsize]);
	obraz.tab = _obraz.get();

	// wype³nianie od o do 10000
	for (size_t i = 0; i < obraz.tabsize; i++)
		_obraz[i] = i;
	// test wype³nienia lewy górny róg
	{
		UINT16 res;
		res = getPoint(&obraz, 0, 0);
		EXPECT_EQ(res, 0);
	}
	// test wype³nienia prawy dolny róg
	{
		UINT16 res;
		res = getPoint(&obraz, 99, 99);
		EXPECT_EQ(res, 10000 - 1);
	}
	// test wype³nienia koniec pierwszego wiersza
	{
		UINT16 res;
		res = getPoint(&obraz, 0, 99);
		EXPECT_EQ(res, 99);
	}
	// maska 5 x 5
	// | 97, 97| 97, 98| 97, 99|| 97,100| 97,101|
	// | 98, 97| 98, 98| 98, 99|| 98,100| 98,101|
	// | 99, 97| 99, 98| 99, 99|| 99,100| 99,101|
	// ------------------------------------------
	// |100, 97|100, 98|100, 99||100,100|100,101|
	// |101, 97|101, 98|101, 99||101,100|101,101|
	//  
	// od prawego dolnego rogu (99,99) -> 9999
	// 
	// |9797|9798|9799||9798|9797|
	// |9897|9898|9899||9898|9897|
	// |9997|9998|9999||9998|9997|
	// ------------------------------
	// |9897|9898|9899||9898|9897|
	// |9797|9798|9799||9798|9797|
	// Bez odbijania
	{
		UINT16 res;
		// II cwiartka
		res = getPoint(&obraz, 99, 99); EXPECT_EQ(res, 9999);
		res = getPoint(&obraz, 99, 98); EXPECT_EQ(res, 9998);
		res = getPoint(&obraz, 99, 97); EXPECT_EQ(res, 9997);

		res = getPoint(&obraz, 98, 99); EXPECT_EQ(res, 9899);
		res = getPoint(&obraz, 98, 98); EXPECT_EQ(res, 9898);
		res = getPoint(&obraz, 98, 97); EXPECT_EQ(res, 9897);

		res = getPoint(&obraz, 97, 99); EXPECT_EQ(res, 9799);
		res = getPoint(&obraz, 97, 98); EXPECT_EQ(res, 9798);
		res = getPoint(&obraz, 97, 97); EXPECT_EQ(res, 9797);
		// I cwiartka
		res = getPoint(&obraz, 99, 100); EXPECT_EQ(res, 9998);
		res = getPoint(&obraz, 99, 101); EXPECT_EQ(res, 9997);

		res = getPoint(&obraz, 98, 100); EXPECT_EQ(res, 9898);
		res = getPoint(&obraz, 98, 101); EXPECT_EQ(res, 9897);

		res = getPoint(&obraz, 97, 100); EXPECT_EQ(res, 9798);
		res = getPoint(&obraz, 97, 101); EXPECT_EQ(res, 9797);
		// IV cwiartka
		res = getPoint(&obraz, 100, 100); EXPECT_EQ(res, 9898);
		res = getPoint(&obraz, 100, 101); EXPECT_EQ(res, 9897);

		res = getPoint(&obraz, 101, 100); EXPECT_EQ(res, 9798);
		res = getPoint(&obraz, 101, 101); EXPECT_EQ(res, 9797);
		// III cwiartka
		res = getPoint(&obraz, 100, 99); EXPECT_EQ(res, 9899);
		res = getPoint(&obraz, 100, 98); EXPECT_EQ(res, 9898);
		res = getPoint(&obraz, 100, 97); EXPECT_EQ(res, 9897);

		res = getPoint(&obraz, 101, 99); EXPECT_EQ(res, 9799);
		res = getPoint(&obraz, 101, 98); EXPECT_EQ(res, 9798);
		res = getPoint(&obraz, 101, 97); EXPECT_EQ(res, 9797);
	}
}