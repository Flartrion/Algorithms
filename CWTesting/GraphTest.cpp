#include "unittest++/unittest++.h"
#include "../CW/Graph.hpp"

SUITE (GraphTests) {

	SUITE (inputTesting) {
		TEST_FIXTURE (Graph, TestGraph_inputCorrupted) {
			CHECK_THROW (input ("inCorrupted.txt"), std::invalid_argument);
		}
		
		TEST_FIXTURE (Graph, TestGraph_inputLackOfNumber) {
			CHECK_THROW (input ("inLackofNumber.txt"), std::invalid_argument);
		}
		
		TEST_FIXTURE (Graph, TestGraph_inputNoSource) {
			CHECK_THROW (input ("inNoSource.txt"), std::invalid_argument);
		}
		
		TEST_FIXTURE (Graph, TestGraph_inputNoDrain) {
			CHECK_THROW (input ("inNoDrain.txt"), std::invalid_argument);
		}
		
		TEST_FIXTURE (Graph, TestGraph_inputNegative) {
			CHECK_THROW (input ("inNegative.txt"), std::invalid_argument);
		}
		
		TEST_FIXTURE (Graph, TestGraph_inputLackOfNode) {
			CHECK_THROW (input ("inLackOfNode.txt"), std::invalid_argument);
		}
		
		TEST_FIXTURE (Graph, TestGraph_inputAsymmetry) {
			CHECK_THROW (input ("inAsymmetry.txt"), std::invalid_argument);
		}
		
		TEST_FIXTURE (Graph, TestGraph_inputEmptyLine) {
			CHECK_THROW (input ("inEmptyLine.txt"), std::invalid_argument);
		}
		
		TEST_FIXTURE (Graph, TestGraph_inputNoFile) {
			CHECK_THROW (input ("something.txt"), std::invalid_argument);
		}
		
		TEST_FIXTURE (Graph, TestGraph_input) {
			input ("in.txt");
			
			CHECK_EQUAL (4, nodes_->getLength());
			
			CHECK_EQUAL (8, matrice_[0][1]);
			CHECK_EQUAL (4, matrice_[0][2]);
			CHECK_EQUAL (4, matrice_[1][2]);
			CHECK_EQUAL (4, matrice_[1][3]);
			CHECK_EQUAL (4, matrice_[3][2]);
		}
	}
	
	TEST (TestGraph_solveBasic) {
		Graph* solver = new Graph;
		solver->input ("in.txt");
		CHECK_EQUAL (12, solver->solve());
		delete solver;
		
		solver = new Graph;
		solver->input ("in2.txt");
		CHECK_EQUAL (5, solver->solve());
		delete solver;
	}
	
	TEST (TestGraph_solveUnusial) {
		Graph* solver = new Graph;
		solver->input ("inLoops.txt");
		CHECK_EQUAL (8, solver->solve());
		delete solver;
		
		solver = new Graph;
		solver->input ("inNoWay.txt");
		CHECK_EQUAL (0, solver->solve());
		delete solver;
	}
}
