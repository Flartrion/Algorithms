#include <unittest++/unittest++.h>
#include "../CW/NodeList.hpp"
SUITE (NodeListTests) {

	TEST_FIXTURE (NodeList, add) {
		pushBack ('S');
		pushBack ('T');
		
		CHECK_EQUAL (2, length_);
	}
	
	TEST_FIXTURE (NodeList, access) {
		pushBack ('T');
		pushBack ('S');
		pushBack ('W');
		
		CHECK_EQUAL ('S', at (1));
		CHECK_EQUAL ('T', at (0));
		CHECK_EQUAL ('W', at (2));
		
		CHECK_THROW (at (3), std::out_of_range);
		CHECK_THROW (at (-1), std::invalid_argument);
		
		CHECK_EQUAL (0, find ('T'));
		CHECK_EQUAL (-1, find ('K'));
	}
	
	TEST_FIXTURE (NodeList, unique) {
		pushBack ('S');
		pushBack ('T');
		
		CHECK_EQUAL (2, length_);
		
		addUnique ('S');
		CHECK_EQUAL (2, length_);
		
		addUnique ('W');
		CHECK_EQUAL (3, length_);
	}
}
