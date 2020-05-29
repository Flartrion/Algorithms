#include <unittest++/unittest++.h>
#include "../LR3/Graph.hpp"

TEST_FIXTURE (Graph, graph_input) {
	CHECK_THROW (input ("corruptedNA.txt"), std::invalid_argument);
	CHECK_THROW (input ("aaa.txt"), std::invalid_argument);
	CHECK_THROW (input ("lackOfNumber.txt"), std::invalid_argument);
	input ("matriceTest.txt");
	
	CHECK_EQUAL (0, matrice_[0][0] + matrice_[1][1] + matrice_[2][2]);
	CHECK_EQUAL (INT_MAX, matrice_[0][2]);
	CHECK_EQUAL (INT_MAX, matrice_[2][0]);
	CHECK_EQUAL (1, matrice_[0][1]);
	CHECK_EQUAL (1, matrice_[1][0]);
	CHECK_EQUAL (1, matrice_[1][2]);
	CHECK_EQUAL (1, matrice_[2][1]);
}

TEST_FIXTURE (Graph, graph_solving) {
	input ("matriceTest.txt"); // since it's pretty suitable. Why not?
	
	solveFordBellman (2);
	CHECK_EQUAL (1, prev_[0]);
	CHECK_EQUAL (2, distance_[0]);
	
	solveFordBellman (0);
	CHECK_EQUAL (1, prev_[2]);
	CHECK_EQUAL (2, distance_[2]);
}
