#include <iostream>
#include "Graph.hpp"
#include <stdexcept>

int main () {
	Graph* solver = new Graph;
	
	try {
		solver->input ("in.txt");
		solver->initEdmondsKarpIterator();
	} catch (std::exception err) {
		std::cout << err.what();
	}
	
	std::cin.ignore ();
	return 0;
}
