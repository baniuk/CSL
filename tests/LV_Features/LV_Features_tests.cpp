/**
* \file    LV_Features_tests.cpp
* \brief	Tests of public and private functions in LV_Features
* \author  PB
* \date    2015/02/23
*/

#include <windows.h>
#include <memory>
#include "gtest/gtest.h"
#include "definitions.h"
#include "LV_Features/PCA.h"

using namespace std;

TEST(PCA_static, simple_test_1)
{
	double DD[2];
	unique_ptr<double> cov(new double[4]);
	PCA(cov.get(), 2, 2, DD);
}