#include <unittest++/unittest++.h>
#include <iostream>
#include "Map.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// To add a test, simply put the following code in the a .cpp file of your choice:
//
// =================================
// Simple Test
// =================================
//
//  TEST(YourTestName)
//  {
//  }
//
// The TEST macro contains enough machinery to turn this slightly odd-looking syntax into legal C++, and automatically register the test in a global list.
// This test list forms the basis of what is executed by RunAllTests().
//
// If you want to re-use a set of test data for more than one test, or provide setup/teardown for tests,
// you can use the TEST_FIXTURE macro instead. The macro requires that you pass it a class name that it will instantiate, so any setup and teardown code should be in its constructor and destructor.
//
//  struct SomeFixture
//  {
//    SomeFixture() { /* some setup */ }
//    ~SomeFixture() { /* some teardown */ }
//
//    int testData;
//  };
//
//  TEST_FIXTURE(SomeFixture, YourTestName)
//  {
//    int temp = testData;
//  }
//
// =================================
// Test Suites
// =================================
//
// Tests can be grouped into suites, using the SUITE macro. A suite serves as a namespace for test names, so that the same test name can be used in two difference contexts.
//
//  SUITE(YourSuiteName)
//  {
//    TEST(YourTestName)
//    {
//    }
//
//    TEST(YourOtherTestName)
//    {
//    }
//  }
//
// This will place the tests into a C++ namespace called YourSuiteName, and make the suite name available to UnitTest++.
// RunAllTests() can be called for a specific suite name, so you can use this to build named groups of tests to be run together.
// Note how members of the fixture are used as if they are a part of the test, since the macro-generated test class derives from the provided fixture class.
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// run all tests
TEST (sanity) { CHECK_EQUAL (1, 1); }

TEST (contains_insert_test) {
    Map<int, int> A;
    A.insert (0, 1);
    A.insert (3, 61);
    A.insert (1, 2);
    A.insert (5, 2);
    A.insert (10, 2);
    CHECK_EQUAL (true, A.contains (0));
    CHECK_EQUAL (true, A.contains (3));
    CHECK_EQUAL (true, A.contains (1));
    CHECK_EQUAL (true, A.contains (5));
    CHECK_EQUAL (true, A.contains (10));
    CHECK_EQUAL (false, A.contains (-5));
}

TEST (lists_test) {
    Map<int, int> A;
    A.insert (0, 1);
    A.insert (3, 61);
    A.insert (1, 2);
    A.insert (5, 2);
    A.insert (10, 2);
    List<int> keys, values;
    keys= A.get_keys ();
    values= A.get_values ();
    CHECK_EQUAL (0, keys.current ());
    keys.go_next ();
    CHECK_EQUAL (1, keys.current ());
    keys.go_next ();
    CHECK_EQUAL (3, keys.current ());
    keys.go_next ();
    CHECK_EQUAL (5, keys.current ());
    keys.go_next ();
    CHECK_EQUAL (10, keys.current ());

    CHECK_EQUAL (1, values.current ());
    values.go_next ();
    CHECK_EQUAL (2, values.current ());
    values.go_next ();
    CHECK_EQUAL (61, values.current ());
    values.go_next ();
    CHECK_EQUAL (2, values.current ());
    values.go_next ();
    CHECK_EQUAL (2, values.current ());

}

TEST (removal_test) {
    Map<int, int> A;
    A.insert (0, 1);
    A.insert (3, 61);
    A.insert (1, 2);
    A.insert (5, 1);
    A.insert (6, 10);
    A.insert (8, 61);
    A.insert (11, 2);
    CHECK_EQUAL(true,A.contains(3));
    CHECK_EQUAL(true,A.contains(11));
    CHECK_EQUAL(true,A.contains(5));
    A.remove(3);
    A.remove(11);
    A.remove(5);
    CHECK_EQUAL(false,A.contains(3));
    CHECK_EQUAL(false,A.contains(11));
    CHECK_EQUAL(false,A.contains(5));
    }

int main () {
    UnitTest::RunAllTests ();
    std::cin.ignore ();
    return 0;
}
