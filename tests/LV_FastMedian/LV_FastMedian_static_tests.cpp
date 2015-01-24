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
 * \test STATIC_FastMedian, _getPoint
 * \brief Tests image wrapping in getPoint
 * \details getPoint can accept coordinates below 0 and above image size.
 * In this case should return mirrored points from inside of the image
 * \pre 100 x 100 image filled from 1 to 10000
 * \post mirrored points
 * \author PB
 * \date 2015/01/24
*/

TEST(STATIC_FastMedian, _getPoint)
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
		ASSERT_EQ(res, 0);
	}
	// test wype³nienia prawy dolny róg
	{
		UINT16 res;
		res = getPoint(&obraz, 99, 99);
		ASSERT_EQ(res, 10000-1);
	}
	// test wype³nienia koniec pierwszego wiersza
	{
		UINT16 res;
		res = getPoint(&obraz, 0, 99);
		ASSERT_EQ(res, 99);
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
		res = getPoint(&obraz, 0, 0); ASSERT_EQ(res, 0);
		res = getPoint(&obraz, 0, 1); ASSERT_EQ(res, 1);
		res = getPoint(&obraz, 0, 2); ASSERT_EQ(res, 2);

		res = getPoint(&obraz, 1, 0); ASSERT_EQ(res, 100);
		res = getPoint(&obraz, 1, 1); ASSERT_EQ(res, 101);
		res = getPoint(&obraz, 1, 2); ASSERT_EQ(res, 102);

		res = getPoint(&obraz, 2, 0); ASSERT_EQ(res, 200);
		res = getPoint(&obraz, 2, 1); ASSERT_EQ(res, 201);
		res = getPoint(&obraz, 2, 2); ASSERT_EQ(res, 202);


	}
}