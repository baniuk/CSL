#include "gtest/gtest.h"
// TODO Dodac dokumentacje wsz�dzie
int main(int argc, char* argv[])
{
	int ret = 0;
	::testing::InitGoogleTest(&argc, argv);
	ret = RUN_ALL_TESTS();
	return ret;
}