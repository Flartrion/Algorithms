#include <unittest++/unittest++.h>
#include "../LR3/CityList.hpp"

TEST_FIXTURE (CityList, List_Add) {
	pushBack (std::string ("City1"));
	pushBack (std::string ("City2"));
	
	CHECK_EQUAL (2, length_);
}

TEST_FIXTURE (CityList, List_Access) {
	pushBack (std::string ("City1"));
	pushBack (std::string ("City2"));
	pushBack (std::string ("City3"));
	
	CHECK_EQUAL (std::string ("City2"), at (1));
	CHECK_EQUAL (std::string ("City1"), at (0));
	CHECK_EQUAL (std::string ("City3"), at (2));
	
	CHECK_THROW (at (3), std::out_of_range);
	CHECK_THROW (at (-1), std::invalid_argument);
	
	CHECK_EQUAL (0, find (std::string ("City1")));
	CHECK_EQUAL (-1, find (std::string ("Whatevs")));
}

TEST_FIXTURE (CityList, List_Unique) {
	pushBack (std::string ("City1"));
	pushBack (std::string ("City2"));
	
	CHECK_EQUAL (2, length_);
	
	addUnique (std::string ("City1"));
	CHECK_EQUAL (2, length_);
	
	addUnique (std::string ("City3"));
	CHECK_EQUAL (3, length_);
}
