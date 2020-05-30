#include <iostream>
#include "Graph.hpp"
#include <stdexcept>

int main () {
	Graph* solver = new Graph;
	
	try {
		solver->input ("in.txt");
		int maxFlow = solver->solve();
		std::cout << "Through presented flow network maximal flow is: " << maxFlow << '\n';
	} catch (std::runtime_error err) {
		std::cout << err.what();
	} catch (std::invalid_argument err) {
		std::cout << err.what();
	} catch (std::out_of_range err) {
		std::cout << err.what();
	}
	
	std::cin.ignore ();
	delete solver;
	return 0;
}
