#include <UnitTest++/UnitTest++.h>
#include "../CW/Graph.hpp"


TEST_FIXTURE (Graph, TestIteratorByWidth_step) {
	input ("in.txt");
	
	IteratorByWidth* stepper = initEdmondsKarpIterator();
	
	CHECK_EQUAL (1, stepper->step());
	CHECK_EQUAL (2, stepper->step());
	CHECK_EQUAL (3, stepper->step());
	CHECK_EQUAL (-1, stepper->step());
	
	delete stepper;
	
	availableConductivity_[0][1] = 4;
	availableConductivity_[0][2] = 0;
	availableConductivity_[1][2] = 0;
	
	stepper = initEdmondsKarpIterator();
	
	CHECK_EQUAL (1, stepper->step());
	CHECK_EQUAL (3, stepper->step());
	CHECK_EQUAL (2, stepper->step());
	CHECK_EQUAL (-1, stepper->step());
	
	delete stepper;
}

TEST_FIXTURE (Graph, TestIteratorByWidth_getCurrentRoutes) {
	input ("in.txt");
	
	IteratorByWidth* stepper = initEdmondsKarpIterator();
	
	while (stepper->step() != -1) {}
	
	int* parents = stepper->getCurrentRoutes();
	
	CHECK_EQUAL (-1, parents[0]);
	CHECK_EQUAL (0, parents[1]);
	CHECK_EQUAL (0, parents[2]);
	CHECK_EQUAL (1, parents[3]);
	
	delete stepper;
	delete[] parents;
	// Same test, a bit different matrice.
	availableConductivity_[0][2] = 0;
	
	stepper = initEdmondsKarpIterator();
	
	while (stepper->step() != -1) {}
	
	parents = stepper->getCurrentRoutes();
	
	CHECK_EQUAL (-1, parents[0]);
	CHECK_EQUAL (0, parents[1]);
	CHECK_EQUAL (1, parents[2]);
	CHECK_EQUAL (1, parents[3]);
	
	delete stepper;
	delete[] parents;
}

TEST_FIXTURE(Graph, TestIteratorByWidth_incorrectConstructor) {
	CHECK_THROW(new IteratorByWidth, std::runtime_error);
}
