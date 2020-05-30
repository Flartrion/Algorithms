#include <iostream>
#include "unittest++/unittest++.h"

TEST(sanity) {
	CHECK_EQUAL(1,1);
}

int main () {
	UnitTest::RunAllTests();
	std::cin.ignore ();
    return 0;
}
