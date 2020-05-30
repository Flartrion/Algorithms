#include <iostream>
#include "Graph.hpp"
#include <stdexcept>

int main () {
	Graph* solver = new Graph;
	
	try {
		solver->input ("in.txt");
//		solver->solve();
	} catch (std::exception err) {
		std::cout << err.what();
	}
	
	std::cin.ignore ();
	delete solver;
	return 0;
}
