#include "Graph.hpp"
#include <iostream>
#include <stdexcept>

int main () {
//	std::setlocale (LC_ALL, "rus");
	Graph* solver = new Graph;
	int a, b;
	
	try {
		solver->input("in.txt");
	} catch (std::exception err) {
		std::cout << err.what();
		std::cin.ignore();
	}
	
	//solver->checkMatrice();
	solver->displayCities();
	
	while (true) {
		std::cout << "\nInput point \"From\": ";
		std::cin >> a;
		std::cout << "Input point \"To\": ";
		std::cin >> b;
		std::cin.ignore();
		
		try {
			solver->solve (a, b);
		} catch (std::invalid_argument err) {
			std::cout << err.what();
			std::cin.ignore();
			break;
		}
	}
	
	
	
	delete solver;
	return 0;
}
