#include "unittest++/unittest++.h"
#include "../CW/Graph.hpp"
#include <iostream>

SUITE (GraphTests) {
	
	TEST_FIXTURE (Graph, TestGraph_input) {
		CHECK_THROW(input("inCorrupted.txt"),std::invalid_argument);
		CHECK_THROW(input("inLackofNumber.txt"),std::invalid_argument);
		input("in.txt");
		
		CHECK_EQUAL(4,nodes_->getLength());
		
		CHECK_EQUAL(8, matrice_[0][1]);
		CHECK_EQUAL(4, matrice_[0][2]);
		CHECK_EQUAL(4, matrice_[1][2]);
		CHECK_EQUAL(4, matrice_[1][3]);
		CHECK_EQUAL(4, matrice_[3][2]);
	}
	
	TEST (TestGraph_solve) {
		Graph* solver = new Graph;
		solver->input("in.txt");
		CHECK_EQUAL(12,solver->solve());
		delete solver;
		
		solver = new Graph;
		solver->input("in2.txt");
		CHECK_EQUAL(5,solver->solve());
		delete solver;
	}
	
	
}
