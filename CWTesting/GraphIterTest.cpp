#include <UnitTest++/UnitTest++.h>
#include "../CW/Graph.hpp"


TEST_FIXTURE(Graph, TestIteratorByWidth_step)
{
	input("in.txt");
	
	IteratorByWidth* stepper = initEdmondsKarpIterator();
	
	CHECK_EQUAL(1,stepper->step());
	CHECK_EQUAL(2,stepper->step());
	CHECK_EQUAL(3,stepper->step());
}

TEST_FIXTURE(Graph, TestIteratorByWidth_getCurrentRoutes)
{
	input("in.txt");
	
	IteratorByWidth* stepper = initEdmondsKarpIterator();
	while (stepper->step() != terminator_) {}
	int* parents = stepper->getCurrentRoutes();
	
	CHECK_EQUAL(-1,parents[0]);
	CHECK_EQUAL(0,parents[1]);
	CHECK_EQUAL(0,parents[2]);
}
