#include <unittest++/unittest++.h>
#include <iostream>
#include "../LR2/ShannonFanoNode.hpp"
#include "../LR2/Map.hpp"
#include <string>

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
TEST (sanity) {
	CHECK_EQUAL (1, 1);
}

TEST_FIXTURE (ShannonFanoNode, ENCODING_SANITY) {
	std::string in = "satisfaction", out;
	CharList* tempInfoHolder = new CharList;
	ShannonFanoNode* root = this;
	Map<char, BinaryHolder>* table;

	for (int i = 0; i<in.length(); i++) {
		tempInfoHolder->add (in[i]);
	}

	setInfo (tempInfoHolder);
	beginSplitting();
	table = generateMap (false);

	int i = 0;

	while (i<in.length()) { // encoding
		BinaryHolder* element = table->findByKey (in[i++]);
		std::string transformer =  std::string (element->binary_);
		out.append (transformer);
	}

	std::string intendedResult ("000001011000001010011100011001101111");
	i = 0;

	while (i<intendedResult.length()) {
		CHECK_EQUAL (intendedResult[i], out[i]);
		i++;
	}

	out.clear();

	i = 0;
	ShannonFanoNode* current = root;

	while (i<intendedResult.length()) { // decoding
		if (intendedResult[i++]=='0') current=current->getLeft();
		else current=current->getRight();

		if (!current->getLeft()) {
			out.push_back (current->getInfo()->getFirstSymbol());
			current=root;
		}
	}

	intendedResult = "satisfaction";
	i = 0;

	while (i<intendedResult.length()) {
		CHECK_EQUAL (intendedResult[i], out[i]);
		i++;
	}

	delete table;
}

TEST_FIXTURE (CharList, LIST_TEST_GENERAL) {
	std::string in ("satisfaction");

	int i = 0;
	while (i<in.length()) {
		add (in[i++]);
	}

	CHECK_EQUAL ('s', at (0)->s_);
	CHECK_EQUAL ('a', at (1)->s_);
	CHECK_EQUAL ('t', at (2)->s_);
	CHECK_EQUAL ('i', at (3)->s_);
	CHECK_EQUAL ('n', at (7)->s_);

	CharList* otherList = split (4);
	CHECK_EQUAL ('i', last_->s_);
	CHECK_EQUAL ('f', otherList->getFirstSymbol());

	CHECK_EQUAL (12, totalWeight() + otherList->totalWeight());
	
	delete otherList;
}

TEST_FIXTURE (CharList, LIST_SPLIT) {
	std::string in ("satisfaction");
	
	int i = 0;
	while (i<in.length()) {
		add (in[i++]);
	}
	
	CharList* otherList = equalSplit();
	CHECK_EQUAL ('t', last_->s_);
	CHECK_EQUAL ('i', otherList->getFirstSymbol());
	
	delete otherList;
}

int main () {
	UnitTest::RunAllTests ();
	std::cin.ignore ();
	return 0;
}
